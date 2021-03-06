/****************************************************************
 *								*
 *	Copyright 2001, 2012 Fidelity Information Services, Inc	*
 *								*
 *	This source code contains the intellectual property	*
 *	of its copyright holder(s), and is made available	*
 *	under a license.  If you do not know the terms of	*
 *	the license, please stop and do not read further.	*
 *								*
 ****************************************************************/

#include "mdef.h"

#include "gtm_ipc.h"
#include "gtm_inet.h"
#include "gtm_fcntl.h"
#include "gtm_string.h"
#include "gtm_unistd.h"
#include "gtm_time.h"

#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <errno.h>
#include <signal.h>	/* for VSIG_ATOMIC_T type */

#include "gdsroot.h"
#include "gtm_facility.h"
#include "fileinfo.h"
#include "gdsbt.h"
#include "gdsfhead.h"
#include "filestruct.h"
#include "gdsblk.h"
#include "gt_timer.h"
#include "jnl.h"
#include "interlock.h"
#include "error.h"
#include "iosp.h"
#include "gdsbgtr.h"
#include "repl_msg.h"
#include "gtmsource.h"
#include "aswp.h"
#include "gtm_c_stack_trace.h"
#include "eintr_wrappers.h"
#include "eintr_wrapper_semop.h"
#include "util.h"
#include "send_msg.h"
#include "change_reg.h"
#include "compswap.h"
#ifdef UNIX
#include "mutex.h"
#endif
#include "gds_rundown.h"
#include "gvusr.h"
#include "do_semop.h"
#include "mmseg.h"
#include "ipcrmid.h"
#include "gtmmsg.h"
#include "wcs_recover.h"
#include "wcs_mm_recover.h"
#include "tp_change_reg.h"
#include "wcs_flu.h"
#include "add_inter.h"
#include "io.h"
#include "gtmsecshr.h"
#include "secshr_client.h"
#include "ftok_sems.h"
#include "gtmimagename.h"
#include "gtmio.h"
#include "have_crit.h"
#include "wcs_clean_dbsync.h"
#include "is_proc_alive.h"
#include "shmpool.h"
#include "db_snapshot.h"
#include "tp_grab_crit.h"
#include "ss_lock_facility.h"

#ifndef GTM_SNAPSHOT
# error "Snapshot facility not available on this platform"
#endif

#define CANCEL_DB_TIMERS(region, csa, cancelled_timer, cancelled_dbsync_timer)	\
{										\
	if (csa->timer)								\
	{									\
		cancel_timer((TID)region);					\
		if (NULL != csa->nl)						\
			DECR_CNT(&csa->nl->wcs_timers, &csa->nl->wc_var_lock);	\
		cancelled_timer = TRUE;						\
		csa->timer = FALSE;						\
	}									\
	if (csa->dbsync_timer)							\
	{									\
		CANCEL_DBSYNC_TIMER(csa);					\
		cancelled_dbsync_timer = TRUE;					\
	}									\
}

GBLREF	VSIG_ATOMIC_T		forced_exit;
GBLREF	boolean_t		mupip_jnl_recover;
GBLREF	boolean_t		created_core, need_core, dont_want_core, is_src_server, is_updproc;
GBLREF	gd_region		*gv_cur_region;
GBLREF	sgmnt_addrs		*cs_addrs;
GBLREF	sgmnt_data_ptr_t	cs_data;
GBLREF	uint4			process_id;
GBLREF	ipcs_mesg		db_ipcs;
GBLREF	jnl_process_vector	*prc_vec;
GBLREF	jnl_process_vector	*originator_prc_vec;
GBLREF 	jnl_gbls_t		jgbl;
GBLREF	boolean_t		dse_running;

LITREF  char                    gtm_release_name[];
LITREF  int4                    gtm_release_name_len;

error_def(ERR_ASSERT);
error_def(ERR_CRITSEMFAIL);
error_def(ERR_DBFILERR);
error_def(ERR_DBRNDWN);
error_def(ERR_RNDWNSKIPCNT);
error_def(ERR_DBRNDWNWRN);
error_def(ERR_GTMASSERT);
error_def(ERR_GTMASSERT2);
error_def(ERR_GTMCHECK);
error_def(ERR_IPCNOTDEL);
error_def(ERR_JNLFLUSH);
error_def(ERR_MEMORY);
error_def(ERR_OUTOFSPACE);
error_def(ERR_RNDWNSEMFAIL);
error_def(ERR_STACKOFLOW);
error_def(ERR_TEXT);
error_def(ERR_WCBLOCKED);
error_def(ERR_STACKOFLOW);

void gds_rundown(void)
{
	boolean_t		cancelled_dbsync_timer, cancelled_timer, have_standalone_access, ipc_deleted, skip_database_rundown;
	boolean_t		is_cur_process_ss_initiator, remove_shm, vermismatch, we_are_last_user, we_are_last_writer, is_mm;
	now_t			now;	/* for GET_CUR_TIME macro */
	char			*time_ptr, time_str[CTIME_BEFORE_NL + 2]; /* for GET_CUR_TIME macro */
	gd_region		*reg;
	int			save_errno, status, rc;
	int4			semval, ftok_semval, sopcnt, ftok_sopcnt;
	short			crash_count;
	sm_long_t		munmap_len;
	sgmnt_addrs		*csa;
	sgmnt_data_ptr_t	csd;
	struct shmid_ds		shm_buf;
	struct sembuf		sop[2], ftok_sop[2];
	uint4           	jnl_status;
	unix_db_info		*udi;
	jnl_private_control	*jpc;
	jnl_buffer_ptr_t	jbp;
	shm_snapshot_t		*ss_shm_ptr;
	uint4			ss_pid, onln_rlbk_pid, holder_pid;
	boolean_t		was_crit;

	jnl_status = 0;
	reg = gv_cur_region;			/* Local copy */

	/* early out for cluster regions
	 * to avoid tripping the assert below.
	 * Note:
	 *	This early out is consistent with VMS.  It has been
	 *	noted that all of the gtcm assignments
	 *      to gv_cur_region should use the TP_CHANGE_REG
	 *	macro.  This would also avoid the assert problem
	 *	and should be done eventually.
	 */
	if (dba_cm == reg->dyn.addr->acc_meth)
		return;

	udi = FILE_INFO(reg);
	csa = &udi->s_addrs;
	csd = csa->hdr;
	assert(csa == cs_addrs && csd == cs_data);
	if ((reg->open) && (dba_usr == csd->acc_meth))
	{
		change_reg();
		gvusr_rundown();
		return;
	}
	ESTABLISH(gds_rundown_ch);
	assert(reg->open);			/* if we failed to open, dbinit_ch should have taken care of proper clean up */
	assert(!reg->opening);			/* see comment above */
	switch(csd->acc_meth)
	{	/* Pass mm and bg through */
		case dba_bg:
			is_mm = FALSE;
			break;
		case dba_mm:
			is_mm = TRUE;
			break;
		case dba_usr:
			assert(FALSE);
		default:
			REVERT;
			return;
	}
	assert(!csa->hold_onto_crit || (csa->now_crit && jgbl.onlnrlbk));
	/* If we are online rollback, we should already be holding crit and should release it only at the end of this module. This
	 * is usually done by noting down csa->now_crit in a local variable (was_crit) and using it whenever we are about to
	 * grab_crit. But, there are instances (like mupip_set_journal.c) where we grab_crit but invoke gds_rundown without any
	 * preceeding rel_crit. Such code relies on the fact that gds_rundown does rel_crit unconditionally (to get locks to a known
	 * state). So, augment csa->now_crit with jgbl.onlnrlbk to track if we can rel_crit unconditionally or not in gds_rundown.
	 */
	was_crit = (csa->now_crit && jgbl.onlnrlbk);
	/* Cancel any pending flush timer for this region by this task */
	cancelled_timer = FALSE;
	cancelled_dbsync_timer = FALSE;
	CANCEL_DB_TIMERS(reg, csa, cancelled_timer, cancelled_dbsync_timer);
	we_are_last_user = FALSE;
	if (!csa->persistent_freeze)
		region_freeze(reg, FALSE, FALSE, FALSE);
	if (!was_crit)
	{
		rel_crit(reg);		/* get locks to known state */
		mutex_cleanup(reg);
	}
	DEFER_INTERRUPTS(INTRPT_IN_GDS_RUNDOWN);
	/* If the process has standalone access, it has udi->grabbed_access_sem set to TRUE at this point. Note that down
	 * in a local variable as the udi->grabbed_access_sem is set to TRUE even for non-standalone access below and hence
	 * we can't rely on that later to determine if the process had standalone access or not when it entered this function.
	 * We need to guarantee that none else access database file header when semid/shmid fields are reset.
	 * We already have created ftok semaphore in db_init or, mu_rndwn_file and did not remove it.
	 * So just lock it. We do it in blocking mode.
	 */
	have_standalone_access = udi->grabbed_access_sem; /* process holds standalone access */
	/* The only process that can invoke gds_rundown while holding access control semaphore is RECOVER/ROLLBACK. All the others
	 * (like MUPIP SET -FILE/MUPIP EXTEND would have invoked db_ipcs_reset() before invoking gds_rundown (from
	 * mupip_exit_handler). The only exception is when these processes encounter a terminate signal and they reach
	 * mupip_exit_handler while holding access control semaphore. Assert accordingly.
	 */
	assert(!have_standalone_access || mupip_jnl_recover || process_exiting);
	/* If we have standalone access, then ensure that a concurrent online rollback cannot be running at the same time as it
	 * needs the access control lock as well. The only expection is we are online rollback and currently running down.
	 */
	onln_rlbk_pid = csa->nl->onln_rlbk_pid;
	assert(!have_standalone_access || mupip_jnl_recover || !onln_rlbk_pid || !is_proc_alive(onln_rlbk_pid, 0));
	skip_database_rundown = FALSE;
	if (!have_standalone_access)
	{
		/* We need to guarantee that no one else access database file header when semid/shmid fields are reset.
		 * We already have created ftok semaphore in db_init or mu_rndwn_file and did not remove it.  So just
		 * lock it. We do it in blocking mode.
		 */
		if (!ftok_sem_lock(reg, FALSE, FALSE))
			rts_error(VARLSTCNT(4) ERR_DBFILERR, 2, DB_LEN_STR(reg));
		FTOK_TRACE(csa, csa->ti->curr_tn, ftok_ops_lock, process_id);
		sop[0].sem_num = 0; sop[0].sem_op = 0;	/* Wait for 0 */
		sop[1].sem_num = 0; sop[1].sem_op = 1;	/* Lock */
		sopcnt = 2;
		sop[0].sem_flg = sop[1].sem_flg = SEM_UNDO | IPC_NOWAIT; /* Don't wait the first time thru */
		SEMOP(udi->semid, sop, sopcnt, status, NO_WAIT);
		if (-1 == status)			/* We couldn't get it in one shot -- see if we already have it */
		{
			save_errno = errno;
			holder_pid = semctl(udi->semid, 0, GETPID);
			if (holder_pid == process_id)
			{
				send_msg(VARLSTCNT(5) MAKE_MSG_INFO(ERR_CRITSEMFAIL), 2,
					DB_LEN_STR(reg),
					ERR_RNDWNSEMFAIL);
				REVERT;
				ENABLE_INTERRUPTS(INTRPT_IN_GDS_RUNDOWN);
				return;			/* Already in rundown for this region */
			}
			if (EAGAIN != save_errno)
			{
				assert(FALSE);
				rts_error(VARLSTCNT(9) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, RTS_ERROR_TEXT("gds_rundown first semop/semctl"), save_errno);
			}
			/* Before attempting again in the blocking mode, see if the holding process is an online rollback.
			 * If so, it is likely we won't get the access control semaphore anytime soon. In that case, we
			 * are better off skipping rundown and continuing with sanity cleanup and exit.
			 */
			skip_database_rundown = (onln_rlbk_pid || csd->file_corrupt);
			if (!skip_database_rundown)
			{
				sop[0].sem_flg = sop[1].sem_flg = SEM_UNDO;	/* Try again - blocking this time */
				SEMOP(udi->semid, sop, 2, status, FORCED_WAIT);
				if (-1 == status)			/* We couldn't get it at all.. */
					rts_error(VARLSTCNT(5) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg), errno);
			}
		}
		udi->grabbed_access_sem = !skip_database_rundown;
	} /* else we we hold the access control semaphore and therefore have standalone access. We do not release it now - we
	   * release it later in mupip_exit_handler.c. Since we already hold the access control semaphore, we don't need the
	   * ftok semaphore and trying it could cause deadlock
	   */
	/* At this point we are guaranteed no one else is doing a db_init/rundown as we hold the access control semaphore */
	assert(csa->ref_cnt);	/* decrement private ref_cnt before shared ref_cnt decrement. */
	csa->ref_cnt--;		/* Currently journaling logic in gds_rundown() in VMS relies on this order to detect last writer */
	assert(!csa->ref_cnt);
	--csa->nl->ref_cnt;
	if (memcmp(csa->nl->now_running, gtm_release_name, gtm_release_name_len + 1))
	{	/* VERMISMATCH condition. Possible only if DSE */
		assert(dse_running);
		vermismatch = TRUE;
	} else
		vermismatch = FALSE;
	if (-1 == shmctl(udi->shmid, IPC_STAT, &shm_buf))
	{
		save_errno = errno;
		rts_error(VARLSTCNT(9) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg),
			ERR_TEXT, 2, RTS_ERROR_TEXT("gds_rundown shmctl"), save_errno);
	} else
		we_are_last_user =  (1 == shm_buf.shm_nattch) && !vermismatch;
	assert(!have_standalone_access || we_are_last_user || jgbl.onlnrlbk); /* recover => one user except ONLINE ROLLBACK */
	if (-1 == (semval = semctl(udi->semid, 1, GETVAL)))
		rts_error(VARLSTCNT(5) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg), errno);
	we_are_last_writer = (1 == semval) && (FALSE == reg->read_only) && !vermismatch;/* There's one writer left and I am it */
	assert(!we_are_last_writer || !skip_database_rundown);
	assert(!we_are_last_user || !skip_database_rundown);
	assert(!(have_standalone_access && !reg->read_only) || we_are_last_writer
			|| jgbl.onlnrlbk); /* recover + R/W region => one writer except ONLINE ROLLBACK */
	if (!have_standalone_access && (-1 == (ftok_semval = semctl(udi->ftok_semid, 1, GETVAL))))
		rts_error(VARLSTCNT(5) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg), errno);
	if (NULL != csa->ss_ctx)
		ss_destroy_context(csa->ss_ctx);
	/* SS_MULTI: If multiple snapshots are supported, then we have to run through each of the snapshots */
	assert(1 == MAX_SNAPSHOTS);
	ss_shm_ptr = (shm_snapshot_ptr_t)SS_GETSTARTPTR(csa);
	ss_pid = ss_shm_ptr->ss_info.ss_pid;
	is_cur_process_ss_initiator = (process_id == ss_pid);
	if (ss_pid && (is_cur_process_ss_initiator || we_are_last_user))
	{
		/* Try getting snapshot crit latch. If we don't get latch, we won't hang for eternity and will skip
		 * doing the orphaned snapshot cleanup. It will be cleaned up eventually either by subsequent MUPIP
		 * INTEG or by a MUPIP RUNDOWN.
		 */
		if (ss_get_lock_nowait(reg) && (ss_pid == ss_shm_ptr->ss_info.ss_pid)
			&& (is_cur_process_ss_initiator || !is_proc_alive(ss_pid, 0)))
		{
			ss_release(NULL);
			ss_release_lock(reg);
		}
	}
	/* If csa->nl->donotflush_dbjnl is set, it means mupip recover/rollback was interrupted and therefore we need not flush
	 * shared memory contents to disk as they might be in an inconsistent state. Moreover, any more flushing will only cause
	 * future rollback to undo more journal records (PBLKs). In this case, we will go ahead and remove shared memory (without
	 * flushing the contents) in this routine. A reissue of the recover/rollback command will restore the database to a
	 * consistent state.
	 */
	if (!csa->nl->donotflush_dbjnl && !reg->read_only && !vermismatch)
	{	/* If we had an orphaned block and were interrupted, set wc_blocked so we can invoke wcs_recover. Do it ONLY
		 * if there is NO concurrent online rollback running (as we need crit to set wc_blocked)
		 */
		if (csa->wbuf_dqd)
		{	/* If we had an orphaned block and were interrupted, mupip_exit_handler will invoke secshr_db_clnup which
			 * will clear this field and so we should never come to gds_rundown with a non-zero wbuf_dqd. The only
			 * exception is if we are recover/rollback in which case gds_rundown (from mur_close_files) is invoked
			 * BEFORE secshr_db_clnup in mur_close_files.
			 * Note: It is NOT possible for online rollback to reach here with wbuf_dqd being non-zero. This is because
			 * the moment we apply the first PBLK, we stop all interrupts and hence can never be interrupted in
			 * wcs_wtstart or wcs_get_space. Assert accordingly.
			 */
			assert(mupip_jnl_recover && !jgbl.onlnrlbk && !skip_database_rundown);
			if (!was_crit)
				grab_crit(reg);
			SET_TRACEABLE_VAR(csd->wc_blocked, TRUE);
			BG_TRACE_PRO_ANY(csa, wcb_gds_rundown);
                        send_msg(VARLSTCNT(8) ERR_WCBLOCKED, 6, LEN_AND_LIT("wcb_gds_rundown"),
                                process_id, &csa->ti->curr_tn, DB_LEN_STR(reg));
			csa->wbuf_dqd = 0;
			wcs_recover(reg);
			if (is_mm)
			{
				assert(FALSE);
				csd = csa->hdr;
			}
			BG_TRACE_PRO_ANY(csa, lost_block_recovery);
			if (!was_crit)
				rel_crit(reg);
		}
		if (JNL_ENABLED(csd) && IS_GTCM_GNP_SERVER_IMAGE)
			originator_prc_vec = NULL;
		/* If we are the last writing user, then everything must be flushed */
		if (we_are_last_writer)
		{	/* Time to flush out all of our buffers */
			if (is_mm)
			{
				if (csa->total_blks != csa->ti->total_blks)	/* do remap if file had been extended */
				{
					if (!was_crit)
						grab_crit(reg);
					wcs_mm_recover(reg);
					csd = csa->hdr;
					if (!was_crit)
						rel_crit(reg);
				}
				csa->nl->remove_shm = TRUE;
			}
			if (csd->wc_blocked && jgbl.onlnrlbk)
			{	/* if the last update done by online rollback was not committed in the normal code-path but was
				 * completed by secshr_db_clnup, wc_blocked will be set to TRUE. But, since online rollback never
				 * invokes grab_crit (since csa->hold_onto_crit is set to TRUE), wcs_recover is never invoked. This
				 * could result in the last update never getting flushed to the disk and if online rollback happened
				 * to be the last writer then the shared memory will be flushed and removed and the last update will
				 * be lost. So, force wcs_recover if we find ourselves in such a situation. But, wc_blocked is
				 * possible only if phase1 or phase2 errors are induced using white box test cases
				 */
				assert(WB_COMMIT_ERR_ENABLED);
				wcs_recover(reg);
			}
			/* Note WCSFLU_SYNC_EPOCH ensures the epoch is synced to the journal and indirectly
			 * also ensures that the db is fsynced. We don't want to use it in the calls to
			 * wcs_flu() from t_end() and tp_tend() since we can defer it to out-of-crit there.
			 * In this case, since we are running down, we don't have any such option.
			 */
			csa->nl->remove_shm = wcs_flu(WCSFLU_FLUSH_HDR | WCSFLU_WRITE_EPOCH | WCSFLU_SYNC_EPOCH);
			/* Since we_are_last_writer, we should be guaranteed that wcs_flu() did not change csd, (in
			 * case of MM for potential file extension), even if it did a grab_crit().  Therefore, make
			 * sure that's true.
			 */
			assert(csd == csa->hdr);
			assert(0 == memcmp(csd->label, GDS_LABEL, GDS_LABEL_SZ - 1));
		} else if (((cancelled_timer && (0 > csa->nl->wcs_timers)) || cancelled_dbsync_timer) && !skip_database_rundown)
		{	/* cancelled pending db or jnl flush timers - flush database and journal buffers to disk */
			if (!was_crit)
				grab_crit(reg);
			/* we need to sync the epoch as the fact that there is no active pending flush timer implies
			 * there will be noone else who will flush the dirty buffers and EPOCH to disk in a timely fashion
			 */
			wcs_flu(WCSFLU_FLUSH_HDR | WCSFLU_WRITE_EPOCH | WCSFLU_SYNC_EPOCH);
			if (!was_crit)
				rel_crit(reg);
			assert((dba_mm == cs_data->acc_meth) || (csd == cs_data));
			csd = cs_data;	/* In case this is MM and wcs_flu() remapped an extended database, reset csd */
		}
		/* Do rundown journal processing after buffer flushes since they require jnl to be open */
		if (JNL_ENABLED(csd))
		{	/* the following tp_change_reg() is not needed due to the assert csa == cs_addrs at the beginning
			 * of gds_rundown(), but just to be safe. To be removed by 2002!! --- nars -- 2001/04/25.
			 */
			tp_change_reg();	/* call this because jnl_ensure_open checks cs_addrs rather than gv_cur_region */
			jpc = csa->jnl;
			jbp = jpc->jnl_buff;
			if (jbp->fsync_in_prog_latch.u.parts.latch_pid == process_id)
                        {
                                assert(FALSE);
                                COMPSWAP_UNLOCK(&jbp->fsync_in_prog_latch, process_id, 0, LOCK_AVAILABLE, 0);
                        }
                        if (jbp->io_in_prog_latch.u.parts.latch_pid == process_id)
                        {
                                assert(FALSE);
                                COMPSWAP_UNLOCK(&jbp->io_in_prog_latch, process_id, 0, LOCK_AVAILABLE, 0);
                        }
			if ((((NOJNL != jpc->channel) && !JNL_FILE_SWITCHED(jpc))
				|| we_are_last_writer && (0 != csa->nl->jnl_file.u.inode)) && !skip_database_rundown)
			{	/* We need to close the journal file cleanly if we have the latest generation journal file open
				 *	or if we are the last writer and the journal file is open in shared memory (not necessarily
				 *	by ourselves e.g. the only process that opened the journal got shot abnormally)
				 * Note: we should not infer anything from the shared memory value of csa->nl->jnl_file.u.inode
				 * 	if we are not the last writer as it can be concurrently updated.
				 */
				if (!was_crit)
					grab_crit(reg);
				if (JNL_ENABLED(csd))
				{
					SET_GBL_JREC_TIME; /* jnl_ensure_open/jnl_put_jrt_pini/pfin/jnl_file_close all need it */
					/* Before writing to jnlfile, adjust jgbl.gbl_jrec_time if needed to maintain time order
					 * of jnl records. This needs to be done BEFORE the jnl_ensure_open as that could write
					 * journal records (if it decides to switch to a new journal file).
					 */
					ADJUST_GBL_JREC_TIME(jgbl, jbp);
					jnl_status = jnl_ensure_open();
					if (0 == jnl_status)
					{	/* If we_are_last_writer, we would have already done a wcs_flu() which would
						 * have written an epoch record and we are guaranteed no further updates
						 * since we are the last writer. So, just close the journal.
						 * Although we assert pini_addr should be non-zero for last_writer, we
						 * play it safe in PRO and write a PINI record if not written already.
						 */
						assert(!jbp->before_images || is_mm
								|| !we_are_last_writer || 0 != jpc->pini_addr);
						if (we_are_last_writer && 0 == jpc->pini_addr)
							jnl_put_jrt_pini(csa);
						if (0 != jpc->pini_addr)
							jnl_put_jrt_pfin(csa);
						/* If not the last writer and no pending flush timer left, do jnl flush now */
						if (!we_are_last_writer && (0 > csa->nl->wcs_timers))
						{
							if (SS_NORMAL == (jnl_status = jnl_flush(reg)))
							{
								assert(jbp->freeaddr == jbp->dskaddr);
								jnl_fsync(reg, jbp->dskaddr);
								assert(jbp->fsync_dskaddr == jbp->dskaddr);
							} else
							{
								send_msg(VARLSTCNT(9) ERR_JNLFLUSH, 2, JNL_LEN_STR(csd),
									ERR_TEXT, 2,
									RTS_ERROR_TEXT("Error with journal flush in gds_rundown"),
									jnl_status);
								assert(NOJNL == jpc->channel);/* jnl file lost has been triggered */
								/* In this routine, all code that follows from here on does not
								 * assume anything about the journaling characteristics of this
								 * database so it is safe to continue execution even though
								 * journaling got closed in the middle.
								 */
							}
						}
						jnl_file_close(reg, we_are_last_writer, FALSE);
					} else
						send_msg(VARLSTCNT(6) jnl_status, 4, JNL_LEN_STR(csd), DB_LEN_STR(reg));
				}
				if (!was_crit)
					rel_crit(reg);
			}
		}
		if (we_are_last_writer)			/* Flush the fileheader last and harden the file to disk */
		{
			if (!was_crit)
				grab_crit(reg);			/* To satisfy crit requirement in fileheader_sync() */
			memset(csd->machine_name, 0, MAX_MCNAMELEN); /* clear the machine_name field */
			if (!have_standalone_access && we_are_last_user)
			{	/* mupip_exit_handler will do this after mur_close_file */
				csd->semid = INVALID_SEMID;
				csd->shmid = INVALID_SHMID;
				csd->gt_sem_ctime.ctime = 0;
				csd->gt_shm_ctime.ctime = 0;
			}
			fileheader_sync(reg);
			if (!was_crit)
				rel_crit(reg);
			if (FALSE == is_mm)
			{
				if (-1 == fsync(udi->fd))		/* Sync it all */
				{
					rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
						  ERR_TEXT, 2, RTS_ERROR_TEXT("Error during file sync at close"), errno);
				}
			} else
			{	/* Now do final MM file sync before exit */
#				if !defined(TARGETED_MSYNC) && !defined(NO_MSYNC)
				if (-1 == fsync(udi->fd))		/* Sync it all */
				{
					rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
						  ERR_TEXT, 2, RTS_ERROR_TEXT("Error during file sync at close"), errno);
				}
#				else
				if (-1 == msync((caddr_t)csa->db_addrs[0], (size_t)(csa->db_addrs[1] - csa->db_addrs[0]), MS_SYNC))
				{
					rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
						  ERR_TEXT, 2, RTS_ERROR_TEXT("Error during file msync at close"), errno);
				}
#				endif
			}
                }
	} /* end if (!reg->read_only && !csa->nl->donotflush_dbjnl) */
	/* We had cancelled all db timers at start of rundown. In case as part of rundown (wcs_flu above), we had started
	 * any timers, cancel them BEFORE setting reg->open to FALSE (assert in wcs_clean_dbsync relies on this).
	 */
	CANCEL_DB_TIMERS(reg, csa, cancelled_timer, cancelled_dbsync_timer);
	if (reg->read_only && we_are_last_user && !have_standalone_access)
	{	/* mupip_exit_handler will do this after mur_close_file */
		db_ipcs.semid = INVALID_SEMID;
		db_ipcs.shmid = INVALID_SHMID;
		db_ipcs.gt_sem_ctime = 0;
		db_ipcs.gt_shm_ctime = 0;
		db_ipcs.fn_len = reg->dyn.addr->fname_len;
		memcpy(db_ipcs.fn, reg->dyn.addr->fname, reg->dyn.addr->fname_len);
		db_ipcs.fn[reg->dyn.addr->fname_len] = 0;
 		/* request gtmsecshr to flush. read_only cannot flush itself */
		if (0 != send_mesg2gtmsecshr(FLUSH_DB_IPCS_INFO, 0, (char *)NULL, 0))
			rts_error(VARLSTCNT(8) ERR_DBFILERR, 2, DB_LEN_STR(reg),
				  ERR_TEXT, 2, RTS_ERROR_TEXT("gtmsecshr failed to update database file header"));
	}
	/* Done with file now, close it */
	CLOSEFILE_RESET(udi->fd, rc);	/* resets "udi->fd" to FD_INVALID */
	if (-1 == rc)
	{
		rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
			  ERR_TEXT, 2, LEN_AND_LIT("Error during file close"), errno);
	}
	/* Unmap storage if mm mode but only the part that is not the fileheader (so shows up in dumps) */
	if (is_mm)
	{
		munmap_len = (sm_long_t)((csa->db_addrs[1] - csa->db_addrs[0]) - ROUND_UP(SIZEOF_FILE_HDR(csa->hdr),
											 MSYNC_ADDR_INCS));
		if (munmap_len > 0)
		{
			munmap((caddr_t)(csa->db_addrs[0] + ROUND_UP(SIZEOF_FILE_HDR(csa->hdr), MSYNC_ADDR_INCS)),
			       (size_t)(munmap_len));
#			ifdef DEBUG_DB64
			rel_mmseg((caddr_t)csa->db_addrs[0]);
#			endif
		}
	}
	/* If we had skipped flushing journal and database buffers due to a concurrent online rollback, increment the counter
	 * indicating that in the shared memory so that online rollback can report the # of such processes when it shuts down.
	 */
	if (skip_database_rundown) /* indicates flushing was skipped */
		csa->nl->dbrndwn_skip_cnt++;
	/* If we are online rollback, report the # of processes that skipped rundown because we were holding the access control
	 * semaphore
	 */
	if (jgbl.onlnrlbk && csa->nl->dbrndwn_skip_cnt)
	{
		send_msg(VARLSTCNT(3) ERR_RNDWNSKIPCNT, 1, csa->nl->dbrndwn_skip_cnt);
		csa->nl->dbrndwn_skip_cnt = 0;
	}
	/* Detach our shared memory while still under lock so reference counts will be correct for the next process to run down
	 * this region. In the process also get the remove_shm status from node_local before detaching.
	 * If csa->nl->donotflush_dbjnl is TRUE, it means we can safely remove shared memory without compromising data
	 * integrity as a reissue of recover will restore the database to a consistent state.
	 */
	remove_shm = !vermismatch && (csa->nl->remove_shm || csa->nl->donotflush_dbjnl);
	rel_crit(reg); /* Since we are about to detach from the shared memory, release crit and reset onln_rlbk_pid */
	if (jgbl.onlnrlbk)
	{	/* We are done with online rollback on this region Indicate to other processes by setting the onln_rlbk_pid to 0 */
		csa->hold_onto_crit = FALSE;
		csa->nl->onln_rlbk_pid = 0;
	}
	status = shmdt((caddr_t)csa->nl);
	csa->nl = NULL; /* dereferencing nl after detach is not right, so we set it to NULL so that we can test before dereference*/
	if (-1 == status)
		send_msg(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg), ERR_TEXT, 2, LEN_AND_LIT("Error during shmdt"), errno);
	REMOVE_CSA_FROM_CSADDRSLIST(csa);	/* remove "csa" from list of open regions (cs_addrs_list) */
	reg->open = FALSE;
	/* If file is still not in good shape, die here and now before we get rid of our storage */
	assertpro(0 == csa->wbuf_dqd);
	ipc_deleted = FALSE;
	/* If we are the very last user, remove shared storage id and the semaphores */
	if (we_are_last_user)
	{	/* remove shared storage, only if last writer to rundown did a successful wcs_flu() */
		assert(!vermismatch);
		if (remove_shm)
		{
			ipc_deleted = TRUE;
			if (0 != shm_rmid(udi->shmid))
				rts_error(VARLSTCNT(8) ERR_DBFILERR, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, RTS_ERROR_TEXT("Unable to remove shared memory"));
		} else if (is_src_server || is_updproc)
		{
			gtm_putmsg(VARLSTCNT(6) ERR_DBRNDWNWRN, 4, DB_LEN_STR(reg), process_id, process_id);
			send_msg(VARLSTCNT(6) ERR_DBRNDWNWRN, 4, DB_LEN_STR(reg), process_id, process_id);
		} else
			send_msg(VARLSTCNT(6) ERR_DBRNDWNWRN, 4, DB_LEN_STR(reg), process_id, process_id);
		/* mupip recover/rollback don't release the semaphore here, but do it later in db_ipcs_reset (invoked from
		 * mur_close_files())
		 */
		if (!have_standalone_access)
		{
			if (0 != sem_rmid(udi->semid))
				rts_error(VARLSTCNT(8) ERR_DBFILERR, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, RTS_ERROR_TEXT("Unable to remove semaphore"));
			udi->grabbed_access_sem = FALSE;
		}
	} else
	{
		assert(!have_standalone_access || jgbl.onlnrlbk);
		if (!jgbl.onlnrlbk)
		{ 	/* If we were writing, get rid of our writer access count semaphore */
			if (!reg->read_only)
				if (0 != (save_errno = do_semop(udi->semid, 1, -1, SEM_UNDO)))
					rts_error(VARLSTCNT(9) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg),
						ERR_TEXT, 2, RTS_ERROR_TEXT("gds_rundown write semaphore release"), save_errno);
			/* Now remove the rundown lock */
			if (!skip_database_rundown)
			{	/* Do it only if we skipped getting the access control semaphore above */
				if (0 != (save_errno = do_semop(udi->semid, 0, -1, SEM_UNDO)))
					rts_error(VARLSTCNT(9) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg),
						ERR_TEXT, 2, RTS_ERROR_TEXT("gds_rundown rundown semaphore release"), save_errno);
				udi->grabbed_access_sem = FALSE;
			}
		} /* else access control semaphore will be released in db_ipcs_reset */
	}
	if (!have_standalone_access)
	{
		if (!ftok_sem_release(reg, !have_standalone_access, FALSE))
				rts_error(VARLSTCNT(4) ERR_DBFILERR, 2, DB_LEN_STR(reg));
		FTOK_TRACE(csa, csa->ti->curr_tn, ftok_ops_release, process_id);
	}
	ENABLE_INTERRUPTS(INTRPT_IN_GDS_RUNDOWN);
	if (!ipc_deleted)
	{
		GET_CUR_TIME;
		if (is_src_server)
			gtm_putmsg(VARLSTCNT(8) ERR_IPCNOTDEL, 6, CTIME_BEFORE_NL, time_ptr,
				LEN_AND_LIT("Source server"), REG_LEN_STR(reg));
		if (is_updproc)
			gtm_putmsg(VARLSTCNT(8) ERR_IPCNOTDEL, 6, CTIME_BEFORE_NL, time_ptr,
				LEN_AND_LIT("Update process"), REG_LEN_STR(reg));
		if (mupip_jnl_recover && (!jgbl.onlnrlbk || !we_are_last_user))
		{
			gtm_putmsg(VARLSTCNT(8) ERR_IPCNOTDEL, 6, CTIME_BEFORE_NL, time_ptr,
				LEN_AND_LIT("Mupip journal process"), REG_LEN_STR(reg));
			send_msg(VARLSTCNT(8) ERR_IPCNOTDEL, 6, CTIME_BEFORE_NL, time_ptr,
				LEN_AND_LIT("Mupip journal process"), REG_LEN_STR(reg));
		}
	}
	REVERT;
}

CONDITION_HANDLER(gds_rundown_ch)
{
	pid_t		sem_pid;
	int		semop_res;
	unix_db_info	*udi;
	sgmnt_addrs	*csa;
	boolean_t	cancelled_timer, cancelled_dbsync_timer, have_standalone_access;

	START_CH;
	/* To get as virgin a state as possible in the core, take the core now if we
	 * would be doing so anyway. This will set created_core so it doesn't happen again.
	 */
	if (DUMPABLE && !SUPPRESS_DUMP)
	{
		need_core = TRUE;
		gtm_fork_n_core();
	}
	udi = FILE_INFO(gv_cur_region);
	csa = &udi->s_addrs;
	/* We got here on an error and are going to close the region. Cancel any pending flush timer for this region by this task*/
	CANCEL_DB_TIMERS(gv_cur_region, csa, cancelled_timer, cancelled_dbsync_timer);
	/* release the access control semaphore, if you hold it */
	have_standalone_access = udi->grabbed_access_sem;
	if (udi->grabbed_access_sem)
	{
		if (csa->now_crit)		/* Might hold crit if wcs_flu or other failure */
		{
			assert(!csa->hold_onto_crit || jgbl.onlnrlbk);
			if (NULL != csa->nl)
				rel_crit(gv_cur_region); /* also sets csa->now_crit to FALSE */
			else
				csa->now_crit = FALSE;
		}
		sem_pid = semctl(udi->semid, 0, GETPID);
		assert(sem_pid == process_id);
		if (0 != (semop_res = do_semop(udi->semid, 0, -1, SEM_UNDO | IPC_NOWAIT)))
			gtm_putmsg(VARLSTCNT(9) ERR_CRITSEMFAIL, 2, DB_LEN_STR(gv_cur_region),
					  ERR_TEXT, 2, RTS_ERROR_TEXT("Error releasing access semaphore"), semop_res);
		udi->grabbed_access_sem = FALSE;

	}
	if (udi->grabbed_ftok_sem)
	{
		assert(!have_standalone_access);
		ftok_sem_release(gv_cur_region, !have_standalone_access, TRUE);
	}
	gv_cur_region->open = FALSE;
	csa->nl = NULL;
	REMOVE_CSA_FROM_CSADDRSLIST(csa); /* remove "csa" from list of open regions (cs_addrs_list) */
	PRN_ERROR;
	gtm_putmsg(VARLSTCNT(4) ERR_DBRNDWN, 2, REG_LEN_STR(gv_cur_region));
	UNWIND(NULL, NULL);
}
