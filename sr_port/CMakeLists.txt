if(ARCHITECTURE_IS_32_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_i386
    ${fis-gtm_SOURCE_DIR}/sr_unix_nsb
    ${fis-gtm_SOURCE_DIR}/sr_unix
    ${fis-gtm_BINARY_DIR}/pro/obj
    )
endif()


if(ARCHITECTURE_IS_64_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_x86_64
    ${fis-gtm_SOURCE_DIR}/sr_unix
    ${fis-gtm_BINARY_DIR}/pro/obj
    )
endif()


include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_linux
  ${fis-gtm_SOURCE_DIR}/pro
  ${fis-gtm_SOURCE_DIR}/pro/obj
  ${fis-gtm_SOURCE_DIR}/sr_port_cm
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/sr_x86_regs
  )


set(GTM_MUMPS_PORT_SRC_C
  act_in_gvt.c
  actuallist.c
  add_atom.c
# add_inter.c    in sr_unix
  adjust_frames.c
  advancewindow.c
  alias_funcs.c
  alloc_reg.c
# append_time_stamp.c    in sr_unix
  asc2i.c
  asc_hex2i.c
# auto_zlink.c      in sr_unix
# auto_zlink_sp.c
  azl_geturxlab.c
  azl_geturxrtn.c
  backup_block.c
# backup_buffer_flush.c    in sr_unix
  base_frame.c
  bit_clear.c
  bit_set.c
  bm_find_blk.c
  bm_getfree.c
  bm_setmap.c
  bml_busy.c
  bml_find_busy.c
  bml_find_free.c
  bml_free.c
  bml_init.c
  bml_newmap.c
  bml_recycled.c
  bml_status_check.c
  bmm_find_free.c
  bmm_init.c
  bool_expr.c
  bt_get.c
  bt_init.c
  bt_malloc.c
  bt_put.c
  bt_refresh.c
  buddy_list.c
  bx_relop.c
  bx_tail.c
  cache_cleanup.c
  cache_get.c
  cache_init.c
  cache_put.c
  cache_stats.c
  cache_table_rebuild.c
  cacheflush.c
# caller_id.o
# callg.o              in sr_unix
# callintogtmxfer.o    in sr_unix
# ccp_cluster_lock_wake.o    in sr_unix
# ccp_fid_msg.o    in sr_unix
# ccp_sendmsg.o    in sr_unix
# ccp_userwait.o    in sr_unix
  cdbg_dump.c
# ce_init.o    in sr_unix
# ce_substitute.o    in sr_unix
# cenable.o    in sr_unix
  ceprep_file.c
  cert_blk.c
  cg_var.c
# ch_cond_core.o    in sr_unix
# ch_overrun.o    in sr_unix
# change_fhead_timer.o    in sr_unix
  change_reg.c
  chktchain.c
# ci_ret_code.o    in sr_unix
# cli.o    in sr_unix
# cli_disallow.o    in sr_unix
  cli_get_str_ele.c
# cli_lex.o    in sr_unix
# cli_parse.o    in sr_unix
  cli_port.c
  cmd.c
# code_gen.o  in  64 bits section below
  coerce.c
  collseq.c
  comp_fini.c
  comp_indr.c
  comp_init.c
# comp_lits.o                 sr_unix
  compile_pattern.c
  compiler_ch.c
  compiler_startup.c
# continue_handler.o in sr_unix
# continue_proc.o in sr_unix
  copy_stack_frame.c
  cre_jnl_file.c
  cre_jnl_file_intrpt_rename.c
  cre_private_code_copy.c
  create_dummy_gbldir.c
  create_fatal_error_zshow_dmp.c
# crit_wake.o in sr_unix in sr_unix
  crit_wake_alarm.c
# ctrap_set.o in sr_unix
# ctrlc_handler.o in sr_unix
  ctrlc_handler_dummy.c
# ctrlc_set.o in sr_unix
# ctrly_set.o in sr_unix
  cvtparm.c
# cvtprot.o in sr_unix
# cvttime.o in sr_unix
  db_auto_upgrade.c
  db_common_init.c
  db_csh_get.c
  db_csh_getn.c
  db_csh_ini.c
  db_csh_ref.c
# dbfilop.o in sr_unix
# dbinit_ch.o in sr_unix
# dbopen_ch.o in sr_unix
# dec_err.o in sr_unix
  deferred_events.c
# deferred_signal_handler.o in sr_unix
  deviceparameters.c
  dfa_calc.c
# disk_block_available.o     in sr_unix
# dm_read.o     in sr_unix
  dm_setup.c
  do_indir_do.c
  do_patalt.c
  do_patfixed.c
  do_patsplit.c
  do_pattern.c
# do_semop.o     in sr_unix
# do_shmat.o     in sr_unix
# do_verify.o     in sr_unix
# do_write.o     in sr_unix
# do_xform.o     in sr_unix
  dollar_quit.c
  dollar_system_init.c
  dollar_zlevel.c
# dollarh.c     in sr_unix
  dollarx.c
  dpgbldir.c
# dpgbldir_sysops.o     in sr_unix
# dsk_read.o     in sr_unix
# dsk_write.o     in sr_unix
# dsk_write_nocache.o     in sr_unix
# dskspace_msg_timer.o     in sr_unix
  dump_lockhist.c
  dumptable.c
  eb_muldiv.c
  ebc_xlat.c
  ecode_add.c
  ecode_get.c
  ecode_init.c
  ecode_set.c
# emit_code.o           in  64bits section below
# emit_code_sp.o           in ???
  entryref.c
  err_check.c
# err_init.o         in sr_unix
# error_return.o         in sr_unix
  eval_expr.c
  ex_tail.c
  exfun_frame.c
  exfunc.c
  expr.c
  expratom.c
  expritem.c
  extern_func.c
# exttab_parse.o    in sr_unix
# exttime.o    in sr_unix
  f_ascii.c
  f_data.c
  f_extract.c
  f_find.c
  f_fnumber.c
  f_fnzbitfind.c
  f_fnzbitget.c
  f_fnzbitset.c
  f_fnzbitstr.c
  f_get.c
  f_incr.c
  f_justify.c
  f_length.c
  f_mint.c
  f_mint_mstr.c
  f_mstr.c
  f_name.c
  f_next.c
  f_one_mval.c
  f_order.c
  f_order1.c
# f_piece.o
  f_qlength.c
  f_qsubscript.c
  f_query.c
  f_reverse.c
  f_select.c
  f_stack.c
  f_text.c
  f_translate.c
  f_two_mstrs.c
  f_two_mval.c
  f_view.c
  f_zahandle.c
  f_zcall.c
  f_zchar.c
  f_zconvert.c
  f_zdate.c
  f_zgetsyi.c
  f_zjobexam.c
  f_zparse.c
  f_zprevious.c
  f_zqgblmod.c
  f_zsearch.c
  f_zsigproc.c
  f_ztrigger.c
  f_ztrnlnm.c
  f_zwidth.c
# fgn_getinfo.o
  fgn_glopref.c
  fgncal_lookup.c
  fgncal_unwind.c
# file_head_read.o
# file_head_write.o
# file_input.o
  find_line_addr.c
# find_line_call.o
  find_line_start.c
  find_rtn_hdr.c
  find_mvstent.c
  five_2_ascii.c
  five_bit.c
  flt_mod.c
  flush_jmp.c
  flush_pio.c
  fnpc_stats.c
  fntext_ch.c
  format2zwr.c
  format_key_lv_val.c
  format_key_mvals.c
  format_lvname.c
  format_targ_key.c
# ftok_sems.o
  gbldefs.c
  gbldefs_usr_share.c
  gds_blk_downgrade.c
  gds_blk_upgrade.c
  gds_map_moved.c
# gds_rundown.o
# gdsfilext.o
# generic_signal_handler.o
# genpat.o
  get_cmd_qlf.c
# get_command_line.o
  get_dir_root.c
  get_dlr_device.c
  get_dlr_key.c
  get_dollar_stack_info.c
  get_frame_creation_info.c
  get_frame_place_mcode.c
  get_fs_block_size.c
# get_full_path.o
  get_lmap.c
  get_log_name.c
  get_mladdr.c
  get_mmseg.c
  get_mvaddr.c
# get_page_size.o
  get_reference.c
  get_ret_targ.c
# get_root.c       not in version 5.5
  get_spec.c
# get_src_line.o
  get_symb_line.c
# geteditor.o
  getjobname.c
# getjobnum.o
  getprime.c
# getstorage.o
  getzdir.c
# getzmode.o
  getzposition.c
# getzprocess.o
  global_map.c
  glvn.c
  goerrorframe.c
  goframes.c
# golevel.o
# goq_load.o
# grab_crit.o
# grab_lock.o
# gt_timers.o
# gtcm_find_reghead.o
# gtcm_jnl_switched.o
  gtm_assert.c
  gtm_assert2.c
# gtm_bintim.o
  gtm_byteswap_64.c
# gtm_c_stack_trace_semop.o
# gtm_compile.o
# gtm_conv.o
# gtm_dbjnl_dupfd_check.o
# gtm_dump.o
# gtm_dump_core.o
  gtm_env_init.c
# gtm_env_init_sp.o
# gtm_env_translate.o
  gtm_env_xlate_init.c
# gtm_event_log.o
# gtm_exit_handler.o
# gtm_fd_trace.o
  gtm_fetch.c
  gtm_ffs.c
# gtm_file_remove.o
# gtm_file_stat.o
# gtm_fork_n_core.o
# gtm_getmsg.o
# gtm_getpwuid.o
# gtm_icu.o
  gtm_imagetype_init.c
# gtm_init_env.o
  gtm_malloc.c
  gtm_malloc_dbg.c
  gtm_maxstr.c
  gtm_memcmp.c
  gtm_newintrinsic.c
# gtm_permissions.o
# gtm_pipe.o
# gtm_putmsg.o
# gtm_putmsg_list.o
  gtm_relqueopi.c
# gtm_rename.o
  gtm_savetraps.c
# gtm_startup.o
# gtm_startup_chk.o
# gtm_stdio.o
# gtm_text_alloc.o
  gtm_threadgbl_init.c
# gtm_trigger.o
# gtm_unique_file_util.o
# gtm_unlink_all.o
# gtm_utf8.o
# gtm_utf8_stx.o
# gtm_wake.o
# gtmci.o
# gtmci_ch.o
# gtmci_isv.o
# gtmci_signals.o
# gtmcrypt_entry.o
# gtmsecshr_sock_cleanup.o
# gtmsecshr_sock_init.o
# gtmsource_jnl_release_timer.o
# gtmsource_losttncomplete.o
# gtmsource_needrestart.o
  gv_bind_name.c
  gv_init_reg.c
  gv_match.c
  gv_rundown.c
# gv_trigger.o  in ??
  gv_xform_key.c
  gvcst_blk_build.c
  gvcst_blk_search.c
  gvcst_bmp_mark_free.c
  gvcst_data.c
  gvcst_dataget.c
  gvcst_delete_blk.c
  gvcst_expand_any_key.c
  gvcst_expand_free_subtree.c
  gvcst_expand_key.c
  gvcst_gblmod.c
  gvcst_get.c
  gvcst_incr.c
  gvcst_init.c
# gvcst_init_sysops.o  in  ??
  gvcst_jrt_null.c
  gvcst_kill.c
  gvcst_kill_blk.c
  gvcst_kill_sort.c
  gvcst_lbm_check.c
  gvcst_lftsib.c
  gvcst_map_build.c
  gvcst_order.c
  gvcst_put.c
  gvcst_query.c
  gvcst_queryget.c
  gvcst_root_search.c
  gvcst_rtsib.c
  gvcst_search.c
  gvcst_tp_init.c
  gvcst_zprevious.c
  gvincr_compute_post_incr.c
  gvincr_recompute_upd_array.c
  gvinit.c
  gvn.c
  gvname_env_restore.c
  gvname_env_save.c
  gvstats_rec.c
  gvstrsub.c
  gvsub2str.c
# gvusr.o      in ??
  gvzwr_arg.c
  gvzwr_fini.c
  gvzwr_init.c
  gvzwr_out.c
  gvzwr_var.c
  gvzwrite_ch.c
  gvzwrite_clnup.c
  hashtab_addr.c
  hashtab_int4.c
  hashtab_int8.c
  hashtab_mname.c
  hashtab_objcode.c
  hashtab_rehash_ch.c
  hashtab_str.c
  have_crit.c
# heartbeat_timer.o
  i2asc.c
  i2hex.c
  i2hex_blkfill.c
  i2hex_nofill.c
# incr_link.o
  ind_cg_var.c
  ind_code.c
  indir_lits.c
  indirection.c
# init_gtm.o       in ??
  init_secshr_addrs.c
  ins_errtriple.c
  ins_triple.c
  insert_region.c
# inst_flush.o       in ??
  int_label.c
# intexpr.c             not in version 5.5
# io_find_mvstent.c     not in version 5.5
# io_get_fgn_driver.o   in ??
  io_init.c
  io_init_ch.c
# io_init_name.o    in ??
# io_is_rm.o    in ??
# io_is_sn.o    in ??
# io_is_tt.o    in ??
# io_open_try.o    in ??
  io_rundown.c
# io_type.o      in ??
# iob_close.o      in ??
# iob_flush.o      in ??
# iob_open_rd.o      in ??
# iob_open_wt.o      in ??
# iob_read.o      in ??
# iob_write.o      in ??
# ioff_open.o      in ??
  iomt_ansilab_manager.c
# iomt_ch.o      in ??
  iomt_close.c
# iomt_closesp.o   in ??
  iomt_dummy.c
  iomt_eof.c
  iomt_erase.c
  iomt_flush.c
  iomt_getrec.c
# iomt_info.o
# iomt_open.o
# iomt_opensp.o
# iomt_qio.o
  iomt_rddoslab.c
# iomt_rdlblk.o
  iomt_rdone.c
  iomt_rdstream.c
  iomt_read.c
  iomt_readblk.c
  iomt_readfl.c
# iomt_reopen.o
  iomt_rewind.c
# iomt_sense.o
  iomt_skipfile.c
  iomt_skiprecord.c
# iomt_tm.o
  iomt_use.c
  iomt_vlflush.c
  iomt_write.c
  iomt_wrtblk.c
  iomt_wrtinit.c
  iomt_wtdoslab.c
  iomt_wteol.c
  iomt_wtff.c
# iomt_wtlblk.o
  iomt_wtone.c
  ionl_close.c
  ionl_dummy.c
  ionl_flush.c
  ionl_open.c
  ionl_rdone.c
  ionl_read.c
  ionl_readfl.c
  ionl_use.c
  ionl_write.c
  ionl_wteol.c
  ionl_wtff.c
  ionl_wtone.c
  iop_parms_size.c
# iopi_iocontrol.o
# iopi_open.o
# iorm_close.o
# iorm_flush.o
# iorm_get.o
# iorm_open.o
# iorm_rdone.o
# iorm_read.o
# iorm_readfl.o
# iorm_use.o
# iorm_write.o
# iorm_wteol.o
  iorm_wtff.c
  iorm_wtone.c
  iosocket_bind.c
  iosocket_close.c
  iosocket_connect.c
  iosocket_create.c
  iosocket_delimiter.c
  iosocket_flush.c
  iosocket_handle.c
  iosocket_iocontrol.c
  iosocket_listen.c
  iosocket_open.c
  iosocket_poolinit.c
  iosocket_rdone.c
  iosocket_read.c
  iosocket_readfl.c
  iosocket_snr.c
  iosocket_switch.c
  iosocket_use.c
  iosocket_wait.c
  iosocket_write.c
  iosocket_wteol.c
  iosocket_wtff.c
  iosocket_wtone.c
  iotcp_close.c
  iotcp_dummy.c
  iotcp_fillroutine.c
  iotcp_flush.c
  iotcp_iocontrol.c
  iotcp_list.c
  iotcp_name2ip.c
  iotcp_open.c
  iotcp_rdone.c
  iotcp_read.c
  iotcp_readfl.c
  iotcp_use.c
  iotcp_write.c
  iotcp_wteol.c
  iotcp_wtff.c
  iotcp_wtone.c
# iott_close.o
  iott_dummy.c
# iott_edit.o
  iott_escape.c
# iott_flush.o
# iott_open.o
# iott_rdone.o
# iott_read.o
# iott_readfl.o
# iott_use.o
# iott_write.o
  iott_wrterr.c
  iott_wteol.c
  iott_wtff.c
  iott_wtone.c
  ious_close.c
  ious_dummy.c
  ious_flush.c
# ious_iocontrol.o
# ious_open.o
# ious_rdone.o
# ious_read.o
# ious_readfl.o
  ious_use.c
# ious_write.o
  ious_wteol.c
  ious_wtff.c
# ious_wtone.o
# ipcrmid.o
  is_canonic_name.c
  is_equ.c
# is_file_identical.o
  is_ident.c
# is_proc_alive.o
# is_raw_dev.o
  jfh_from_jnl_info.c
  jmp_opto.c
  jnl_ensure_open.c
  jnl_file_close.c
# jnl_file_extend.o
  jnl_file_lost.c
# jnl_file_open.o
  jnl_file_open_common.c
  jnl_file_open_switch.c
  jnl_flush.c
  jnl_format.c
# jnl_fsync.o
  jnl_get_checksum.c
  jnl_get_checksum_entire.c
# jnl_output_sp.o
# jnl_prc_vector.o
  jnl_put_jrt_pfin.c
  jnl_put_jrt_pini.c
  jnl_send_oper.c
  jnl_wait.c
  jnl_write.c
  jnl_write_aimg_rec.c
  jnl_write_attempt.c
  jnl_write_eof_rec.c
  jnl_write_epoch_rec.c
  jnl_write_inctn_rec.c
  jnl_write_logical.c
  jnl_write_pblk.c
  jnl_write_poolonly.c
  jnl_write_ztp_logical.c
  jnl_write_trunc_rec.c
# jnlpool_init.o     in sr_unix
# jobchild_init.o
  jobexam_process.c
# jobexam_signal_handler.o
  jobinterrupt_event.c
  jobinterrupt_init.c
  jobinterrupt_process.c
  jobinterrupt_process_cleanup.c
  jobparameters.c
  la_encrypt.c
  lastchance1.c
  lastchance2.c
  lastchance3.c
  lb_init.c
  lckclr.c
  lcl_arg1_is_desc_of_arg2.c
  line.c
  linetail.c
  lk_check_own.c
# lke_cmd_disallow.c    in sr_unix
# lke_ctrlc_handler.c   in sr_unix
  lkglvn.c
  lkinit.c
  logical_truth_value.c
  lookup_variable_htent.c
  lower_to_upper.c
  lref.c
# lref_parse.o     in sr_unix
  lv_getslot.c
  lv_kill.c
  lv_killarray.c
  lv_newblock.c
  lv_newname.c
  lv_tree.c
  lv_var_clone.c
  lvn.c
  lvzwr_arg.c
  lvzwr_fini.c
  lvzwr_init.c
  lvzwr_key.c
  lvzwr_out.c
  lvzwr_var.c
  m_break.c
  m_close.c
  m_do.c
  m_else.c
  m_for.c
  m_goto.c
  m_halt.c
  m_hang.c
  m_hcmd.c
  m_if.c
  m_job.c
  m_kill.c
  m_lock.c
  m_merge.c
  m_new.c
  m_open.c
  m_quit.c
  m_read.c
  m_set.c
  m_tcommit.c
  m_trestart.c
  m_trollback.c
  m_tstart.c
  m_use.c
  m_view.c
  m_write.c
  m_xecute.c
  m_zallocate.c
  m_zattach.c
  m_zbreak.c
  m_zcompile.c
  m_zcontinue.c
  m_zdeallocate.c
  m_zedit.c
  m_zhalt.c
  m_zhelp.c
  m_zinvcmd.c
  m_zlink.c
  m_zmessage.c
  m_zprint.c
  m_zshow.c
  m_zstep.c
  m_zsystem.c
  m_ztcommit.c
# m_ztrigger.o    in sr_unix
  m_ztstart.c
  m_zwatch.c
  m_zwithdraw.c
  m_zwrite.c
# make_cimode.o    in Sr_unix
  make_commarg.c
# make_dmode.o     in sr_unix
  make_gvsubsc.c
# make_mode.o     in sr_unix
  maketriple.c
# map_sym.o      in sr_unix
  matchc.c
  mcalloc.c
  mcfree.c
  mdb_condition_handler.c
# mem_access.o     in sr_unix
  memvcmp.c
  merge_desc_check.c
  mlabel2xtern.c
  mlk_bckout.c
  mlk_garbage_collect.c
  mlk_lock.c
  mlk_prcblk_add.c
  mlk_prcblk_delete.c
  mlk_pvtblk_create.c
  mlk_pvtblk_delete.c
  mlk_pvtblk_equ.c
  mlk_pvtblk_insert.c
  mlk_region_lookup.c
  mlk_shr_init.c
  mlk_shrblk_create.c
  mlk_shrblk_delete_if_empty.c
  mlk_shrblk_find.c
  mlk_shrclean.c
  mlk_shrsub_garbage_collect.c
  mlk_tree_wake_children.c
  mlk_unlock.c
  mlk_unpend.c
  mlk_wake_pending.c
  mm_read.c
  mprof_funcs.c
  mprof_stack.c
  mprof_tree.c
  mtables.c
# mu_decrypt.o    in sr_unix
  mu_gv_cur_reg_init.c
  mu_int_wait_rdonly.c
# mumps_clitab.o   in sr_unix
  mupfndfil.c
# mupip_crypt.o    in sr_unix
  mupip_load_ch.c
# mutex.o
  mutex_deadlock_check.c
# mutex_sock_cleanup.o
# mutex_sock_init.o
# mutex_wake_proc.o
  mval2fao.c
  mval2subsc.c
  mval_lex.c
  mval_nongraphic.c
  mval_write.c
  mvalconv.c
  n2s.c
  name_glvn.c
  namelook.c
  new_stack_frame.c
  newtriple.c
  nil_iocontrol.c
  nref.c
  numcmp.c
# numexpr.c      not in version 5.5
# obj_code.o     in sr_unix
# obj_file.o     in sr_unix
# obj_filesp.o     in sr_unix
  oc_tab.c
  oc_tab_graphic.c
# ojchildioclean.o   in sr_unix
# ojchildioset.o   in sr_unix
# ojchildparms.o   in sr_unix
# ojchkfs.o   in sr_unix
# ojgetch_env.o   in sr_unix
# ojparams.o   in sr_unix
# ojstartchild.o   in sr_unix
  one_job_param.c
  op_add.c
  op_bindparm.c
  op_break.c
  op_cat.c
  op_close.c
  op_clralsvars.c
  op_commarg.c
  op_cvtparm.c
  op_decrlock.c
  op_div.c
  op_dmode.c
  op_dt_false.c
  op_dt_get.c
  op_dt_store.c
  op_dt_true.c
  op_exfunret.c
  op_exfunretals.c
  op_exp.c
# op_fgnlookup.o     in sr_unix
  op_fnascii.c
  op_fnchar.c
  op_fndata.c
# op_fnextract.o     in sr_unix
# op_fnfgncal.o     in sr_unix
  op_fnfind.c
  op_fnfnumber.c
  op_fnget2.c
# op_fngetdvi.o     in sr_unix
# op_fngetjpi.o     in sr_unix
# op_fngetlki.o     in sr_unix
# op_fngetsyi.o     in sr_unix
  op_fngvget.c
  op_fngvget1.c
  op_fngvget2.c
  op_fnincr.c
  op_fnj2.c
  op_fnj3.c
  op_fnlength.c
  op_fnlvname.c
  op_fnlvnameo2.c
  op_fnlvprvname.c
  op_fnname.c
  op_fnnext.c
  op_fno2.c
  op_fnorder.c
# op_fnp1.o             in sr_unix
# op_fnpiece.o             in sr_unix
# op_fnpopulation.o             in sr_unix
  op_fnqlength.c
  op_fnqsubscript.c
  op_fnquery.c
# op_fnrandom.o       in sr_unix
  op_fnreverse.c
  op_fnstack1.c
  op_fnstack2.c
  op_fntext.c
  op_fntranslate.c
  op_fnview.c
  op_fnzahandle.c
  op_fnzbitand.c
  op_fnzbitcoun.c
  op_fnzbitfind.c
  op_fnzbitget.c
  op_fnzbitlen.c
  op_fnzbitnot.c
  op_fnzbitor.c
  op_fnzbitset.c
  op_fnzbitstr.c
  op_fnzbitxor.c
# op_fnzcall.o      in sr_unix
# op_fnzconvert.o      in sr_unix
  op_fnzdata.c
  op_fnzdate.c
# op_fnzfile.o      in sr_unix
  op_fnzjobexam.c
# op_fnzlkid.o      in sr_unix
  op_fnzm.c
  op_fnzp1.c
# op_fnzparse.o    in sr_unix
# op_fnzpid.o    in sr_unix
  op_fnzpiece.c
  op_fnzpopulation.c
  op_fnzprevious.c
# op_fnzpriv.o      in sr_unix
  op_fnzqgblmod.c
# op_fnzsearch.o     in sr_unix
# op_fnzsetprv.o     in sr_unix
  op_fnzsigproc.c
  op_fnzsubstr.c
  op_fnztrigger.c
# op_fnztrnlnm.o      in  sr_unix
  op_fnzwidth.c
  op_forfreeindx.c
  op_fornestlvl.c
  op_get_msf.c
  op_getindx.c
  op_gvdata.c
  op_gvextnam.c
  op_gvget.c
  op_gvincr.c
  op_gvkill.c
  op_gvnaked.c
  op_gvname.c
  op_gvnext.c
  op_gvo2.c
  op_gvorder.c
  op_gvput.c
  op_gvquery.c
  op_gvqueryget.c
  op_gvrectarg.c
  op_gvsavtarg.c
  op_gvzwithdraw.c
  op_gvzwrite.c
  op_halt.c
  op_hang.c
  op_hardret.c
# op_horolog.o      in  sr_unix
  op_idiv.c
  op_igetsrc.c
  op_incrlock.c
  op_inddevparms.c
  op_indfnname.c
  op_indfun.c
  op_indget.c
  op_indglvn.c
  op_indincr.c
  op_indlvadr.c
  op_indlvarg.c
  op_indlvnamadr.c
  op_indmerge.c
  op_indname.c
  op_indo2.c
  op_indpat.c
  op_indrzshow.c
  op_indset.c
  op_indtext.c
  op_iocontrol.c
  op_iretmval.c
# op_job.o      in  sr_unix
  op_kill.c
  op_killalias.c
  op_killaliasall.c
  op_killall.c
  op_lkinit.c
  op_lkname.c
  op_lock.c
  op_lock2.c
  op_lvpatwrite.c
  op_lvzwithdraw.c
  op_lvzwrite.c
  op_m_srchindx.c
  op_merge.c
  op_merge_arg.c
  op_mul.c
  op_newintrinsic.c
  op_newvar.c
  op_nullexp.c
  op_oldvar.c
  op_open.c
  op_open_dummy.c
  op_putindx.c
  op_rdone.c
  op_read.c
  op_readfl.c
  op_rhdaddr.c
  op_rterror.c
  op_setals2als.c
  op_setalsct2alsct.c
  op_setalsctin2als.c
  op_setalsin2alsct.c
# op_setextract.o      in  sr_unix
  op_setfnretin2als.c
  op_setfnretin2alsct.c
# op_setp1.o      in  sr_unix
# op_setpiece.o      in  sr_unix
  op_setzbrk.c
  op_setzextract.c
  op_setzp1.c
  op_setzpiece.c
  op_srchindx.c
  op_svget.c
  op_svput.c
  op_tcommit.c
  op_trestart.c
  op_trollback.c
  op_tstart.c
  op_unlock.c
  op_unwind.c
  op_use.c
  op_view.c
  op_write.c
  op_wteol.c
  op_wtff.c
  op_wtone.c
  op_wttab.c
  op_xkill.c
  op_xnew.c
  op_zalloc2.c
  op_zallocate.c
# op_zattach.o      in  sr_unix
  op_zbreak.c
  op_zcompile.c
  op_zcont.c
  op_zdealloc2.c
  op_zdeallocate.c
# op_zedit.o      in  sr_unix
  op_zg1.c
  op_zhalt.c
# op_zhelp_xfr.o      in  sr_unix
# op_zlink.o      in  sr_unix
# op_zmess.o      in  sr_unix
  op_zprevious.c
  op_zprint.c
  op_zshow.c
  op_zst_break.c
  op_zst_over.c
  op_zstep.c
  op_zstepret.c
  op_zsystem.c
  op_ztcommit.c
# op_ztrigger.o      in  sr_unix
  op_ztstart.c
  op_zwritesvn.c
# outc.o      in  sr_unix
  outofband_action.c
  outofband_clear.c
# parse_file.o      in  sr_unix
  parm_pool.c
  parse_trctbl_groups.c
  parse_until_rparen_or_space.c
  pat_compress.c
  pat_unwind.c
  patmaskseq.c
  patstr.c
  pattab.c
  performcaslatchcheck.c
# pipeint_stats.o      in  sr_unix
  preemptive_ch.c
  prepare_unique_name.c
  print_exit_stats.c
  print_target.c
# probe.o      in  sr_unix
  process_deferred_stale.c
  process_gvt_pending_list.c
  promodemo.c
  push_lvval.c
  push_mval.c
# push_parm.c     not in version V55000
  push_stck.c
  push_tval.c
  put_cdlt.c
  put_ilit.c
  put_indr.c
  put_lit.c
  put_mfun.c
  put_mlab.c
  put_mmseg.c
  put_mnxl.c
  put_mvar.c
  put_ocnt.c
  put_str.c
  put_tjmp.c
  put_tnxt.c
  put_tref.c
  put_tsiz.c
# random.o      in  sr_unix
# rc_cpt_ops.o      in  sr_unix
  real_len.c
  region_freeze.c
  region_init.c
  region_init_ch.c
  reinit_externs.c
# rel_crit.o      in  sr_unix
# rel_lock.o      in  sr_unix
  rel_mmseg.c
  release_private_code_copy.c
  relqueop.c
  relqueopi.c
# remove_rms.o      in  sr_unix
  rename_file_if_exists.c
  repl_errno.c
# repl_instance.o      in  sr_unix
# repl_sem.o      in  sr_unix
  repl_sort_tr_buff.c
  replication_ch.c
# resetterm.o      in sr_unix
  resolve_blocks.c
  resolve_lab.c
  resolve_ref.c
  rtnlaboff2entryref.c
# rts_error.o      in sr_unix
  rwformat.c
  s2n.c
  s2pool.c
  s2pool_align.c
# same_device_check.o      in  sr_unix
  sec_shr_blk_build.c
  sec_shr_map_build.c
# secshr_client.o      in  sr_unix
  secshr_db_clnup.c
  semwt2long_handler.c
# send_msg.o            in sr_unix
# set_jnl_file_close.o            in sr_unix
  set_jnl_info.c
# set_num_additional_processors.o      in  sr_unix
  set_testpoint.c
# set_zstatus.o      in  sr_unix
  setcurtchain.c
# setterm.o      in  sr_unix
  setzdir.c
  seven_2_ascii.c
  sgnl_gvnulsubsc.c
  sgnl_gvreplerr.c
  sgnl_gvundef.c
# sgtm_putmsg.o      in  sr_unix
  shmpool.c
  show_source_line.c
# shrink_trips.o      in  64 bits section
  shuffq.c
# sig_init.o      in  sr_unix
  skpc.c
# sleep.o      in  sr_unix
  sockint_stats.c
  sorts_after.c
# source_file.o              in sr_unix
# ss_context_mgr.o              in sr_unix
# ss_lock_facility.o              in sr_unix
# ss_release.o              in sr_unix
# ss_shdw_mgr.o              in sr_unix
# ss_write_block.o              in sr_unix
  start_fetches.c
  start_for_fetches.c
# std_dev_outbndset.o          in  src_unix
# stop_image.o          in  src_unix
# stop_image_ch.o          in  src_unix
  stp_expand_array.c
  stp_gcol.c
  stp_gcol_ch.c
  stp_init.c
  stp_move.c
  stpg_sort.c
  str2gvargs.c
  str2gvkey_gvfunc.c
  str2gvkey_nogvfunc.c
# str_match.o      in  sr_unix
# strexpr.c        not in version 5.5
  strpiecediff.c
  stx_error.c
  sub2stbl.c
# suspend.o      in  sr_unix
# suspsigs_handler.o      in  sr_unix
  symb_line.c
  symbinit.c
  t_abort.c
  t_begin.c
  t_begin_crit.c
  t_busy2free.c
  t_ch.c
  t_commit_cleanup.c
  t_create.c
  t_end.c
  t_end_sysops.c
  t_qread.c
  t_retry.c
  t_write.c
  t_write_map.c
  t_write_root.c
  targ_alloc.c
  tcp_open.c
# term_setup.o      in  sr_unix
  terminate_ch.c
  time_calc.c
  timeout2msec.c
  tnxtarg.c
  tp_change_reg.c
  tp_clean_up.c
  tp_cw_list.c
  tp_get_cw.c
# tp_grab_crit.o      in  sr_unix
  tp_hist.c
  tp_incr_clean_up.c
  tp_incr_commit.c
  tp_restart.c
  tp_set_sgm.c
  tp_tend.c
  tp_timeout.c
  tp_timeout_dummy.c
  tp_unwind.c
  tpdefs.c
  trans_code.c
  trans_code_cleanup.c
# trans_log_name.o      in  sr_unix
  trans_numeric.c
# trigger_cmd.o          in sr_unix
# trigger_compare.o          in sr_unix
# trigger_delete.o          in sr_unix
# trigger_fill_xecute_buffer.o          in sr_unix
# trigger_gbl_fill_xecute_buffer.o          in sr_unix
# trigger_incr_cycle.o          in sr_unix
# trigger_parse.o          in sr_unix
# trigger_read_name_entry.o          in sr_unix
# trigger_scan_string.o          in sr_unix
# trigger_select.o          in sr_unix
# trigger_source_read_andor_verify.o          in sr_unix
# trigger_tpwrap_ch.o          in sr_unix
# trigger_trgfile.o          in sr_unix
# trigger_update.o          in sr_unix
# trigger_user_name.o          in sr_unix
  tripinit.c
  tt_write_error_set.c
# ttt.o      generated in pro/obj
  underr.c
  undx.c
  unw_mv_ent.c
  unw_retarg.c
  unwind_nocounts.c
  upper_to_lower.c
  urx_add.c
  urx_addlab.c
  urx_addrtn.c
  urx_free.c
  urx_getlab.c
  urx_getrtn.c
  urx_putlab.c
  urx_putrtn.c
# urx_remove.o      in  sr_unix
  util_base_ch.c
  util_ch.c
# util_exit_handler.o   in  sr_unix
# util_in_open.o   in  sr_unix
# util_input.o   in  sr_unix
# util_output.o   in  sr_unix
# util_output_cm.o   in  sr_unix
# util_spawn.o   in  sr_unix
  val_iscan.c
  valid_labname.c
  valid_mname.c
  verify_queue.c
  view_arg_convert.c
  view_jnlfile.c
  view_routines.c
  viewkeys.c
  wait_for_block_flush.c
  wake.c
  wake_alarm.c
  walktree.c
  wbox_test_init.c
  wcs_backoff.c
# wcs_clean_dbsync.o      in  sr_unix
# wcs_clean_dbsync_timer.o      in  sr_unix
# wcs_flu.o      in  sr_unix
# wcs_get_space.o      in  sr_unix
  wcs_phase2_commit_wait.c
  wcs_read_in_progress_wait.c
  wcs_recover.c
  wcs_sleep.c
  wcs_verify.c
# wcs_write_in_progress_wait.o      in  sr_unix
# wcs_wtstart.o      in  sr_unix
  wrtcatopt.c
  xfer_name.c
  xfer_table.c
# zcall_package.o      in  sr_unix
  zco_init.c
  zdate_form_init.c
# zl_cmd_qlf.o      in  sr_unix
  zlcompile.c
# zlmov_lnames.o      in  sr_unix
  zr_find.c
  zr_get_free.c
  zr_init.c
  zr_put_free.c
  zr_remove.c
# zro_gettok.o      in  sr_unix
  zro_init.c
# zro_load.o      in  sr_unix
# zro_search.o      in  sr_unix
# zro_shlibs.o      in  sr_unix
# zshow_ch.c       problem with undefined symbol: zwr_output_buff
# zshow_devices.o      in  sr_unix
  zshow_format_lock.c
  zshow_gvstats.c
  zshow_locks.c
  zshow_output.c
  zshow_stack.c
  zshow_svn.c
  zshow_zbreaks.c
# zshow_zcalls.o      in  sr_unix
  zshow_zwrite.c
  ztrap_form_init.c
  ztrap_new_init.c
  ztrap_save_ctxt.c
  zwr2format.c
  zyerror_init.c
  op_labaddr.c
  mu_gv_stack_init.c
  )

#
#  Prepare sources for library libmupip
#
set(GTM_MUPIP_PORT_SRC_C
# bin_load.o      in  sr_unix
# db_ipcs_reset.o      in  sr_unix
  desired_db_format_set.c
  ext2jnl.c
# go_load.o      in  sr_unix
  gtm_tempnam.c
# gtm_zlib.o      in  sr_unix
# gtmrecv.o      in  sr_unix
  gtmrecv_ch.c
  gtmrecv_changelog.c
  gtmrecv_checkhealth.c
  gtmrecv_comm_init.c
# gtmrecv_end.o      in  sr_unix
  gtmrecv_end_helpers.c
  gtmrecv_exit.c
# gtmrecv_fetchresync.o      in  sr_unix
  gtmrecv_get_opt.c
  gtmrecv_helpers_init.c
# gtmrecv_poll_actions.o      in  sr_unix
# gtmrecv_process.o      in  sr_unix
  gtmrecv_reap_helpers.c
  gtmrecv_reinit_logseqno.c
  gtmrecv_showbacklog.c
# gtmrecv_shutdown.o      in  sr_unix
  gtmrecv_start_helpers.c
  gtmrecv_statslog.c
  gtmrecv_upd_proc_init.c
# gtmsource.o      in  sr_unix
  gtmsource_ch.c
# gtmsource_changelog.o      in  sr_unix
# gtmsource_checkhealth.o      in  sr_unix
  gtmsource_comm_init.c
  gtmsource_ctl_init.c
# gtmsource_end.o      in  sr_unix
  gtmsource_exit.c
# gtmsource_flush_fh.o      in  sr_unix
# gtmsource_get_opt.o      in  sr_unix
# gtmsource_heartbeat.o      in  sr_unix
# gtmsource_jnlpool.o      in  sr_unix
# gtmsource_mode_change.o      in  sr_unix
  gtmsource_poll_actions.c
# gtmsource_process.o      in  sr_unix
# gtmsource_process_ops.o      in  sr_unix
# gtmsource_readfiles.o      in  sr_unix
# gtmsource_readpool.o      in  sr_unix
  gtmsource_reinit_logseqno.c
# gtmsource_rootprimary_init.o      in  sr_unix
# gtmsource_seqno_init.o      in  sr_unix
# gtmsource_showbacklog.o      in  sr_unix
# gtmsource_shutdown.o      in  sr_unix
# gtmsource_statslog.o      in  sr_unix
# gtmsource_stopfilter.o      in  sr_unix
  gv_select.c
  jnl2ext.c
# jnl_setver.c        not in version 5.5
# jnlext_write.o      in  sr_unix
  jnlpool_hasnt_overflowed.c
# mu_all_version_standalone.o
  mu_clsce.c
# mu_cre_file.o
# mu_cre_structs.o
  mu_dwngrd_header.c
  mu_extr_gblout.c
  mu_extr_getblk.c
  mu_extr_ident.c
# mu_extract.o
# mu_file_size.o
  mu_freeze_ch.c
# mu_getlst.o      in  sr_unix
# mu_gvis.o      in  sr_unix
  mu_int_blk.c
  mu_int_err.c
  mu_int_fhead.c
  mu_int_getkey.c
  mu_int_init.c
  mu_int_maps.c
  mu_int_read.c
  mu_int_reg.c
  mu_int_reg_ch.c
  mu_int_write.c
# mu_op_open.o      in  sr_unix
# mu_outofband_setup.o      in  sr_unix
  mu_put_gvdata.c
  mu_reduce_level.c
  mu_reorg.c
  mu_reorg_upgrd_dwngrd.c
# mu_replpool_grab_sem.o
# mu_replpool_remove_sem.o
# mu_rndwn_all.o
# mu_rndwn_file.o
# mu_rndwn_repl_instance.o
# mu_rndwn_replpool.o
# mu_signal_process.o
  mu_split.c
  mu_swap_blk.c
# mu_term_setup.o      in  sr_unix
# mu_trig_trgfile.o      in  sr_unix
  mu_upgrd_dngrd_confirmed.c
  mu_upgrd_header.c
  mubclnup.c
# mubexpfilnam.o      in  sr_unix
# mubfilcpy.o      in  sr_unix
  mubfndreg.c
# mubgetfil.o      in  sr_unix
# mubinccpy.o      in  sr_unix
# mucblkini.o      in  sr_unix
  mucregini.c
# mup_bak_sys.o      in  sr_unix
  mupip_backup.c
# mupip_cmd_disallow.o      in  sr_unix
  mupip_create.c
# mupip_ctrl.o      in  sr_unix
# mupip_cvtgbl.o      in  sr_unix
# mupip_cvtpgm.o      in  sr_unix
  mupip_downgrade.c
# mupip_endiancvt.o      in  sr_unix
# mupip_exit.o      in  sr_unix
# mupip_exit_handler.o      in  sr_unix
  mupip_extend.c
  mupip_freeze.c
# mupip_ftok.o      in  sr_unix
# mupip_help.o      in  sr_unix
  mupip_integ.c
  mupip_intrpt.c
# mupip_quit.o      in  sr_unix
  mupip_recover.c
  mupip_reorg.c
# mupip_restore.o      in  sr_unix
# mupip_rundown.o      in  sr_unix
  mupip_set.c
# mupip_set_file.o      in  sr_unix
  mupip_set_jnl_ch.c
  mupip_set_jnl_cleanup.c
  mupip_set_jnlfile_aux.c
  mupip_set_journal.c
  mupip_set_journal_fname.c
  mupip_set_journal_newstate.c
  mupip_set_journal_parse.c
  mupip_stop.c
# mupip_trigger.o      in  sr_unix
  mupip_upgrade.c
# mupip_upgrade_standalone.o      in  sr_unix
  mur_apply_pblk.c
  mur_back_process.c
  mur_block_count_correct.c
  mur_blocks_free.c
  mur_close_file_extfmt.c
  mur_close_files.c
# mur_cre_file_extfmt.o     in sr_unix
  mur_db_files_from_jnllist.c
  mur_do_wildcard.c
  mur_forward.c
  mur_forward_play_cur_jrec.c
  mur_forward_play_multireg_tp.c
  mur_gbldefs.c
  mur_get_options.c
  mur_get_pini.c
  mur_init.c
  mur_insert_prev.c
  mur_interactive.c
  mur_jctl_from_next_gen.c
  mur_jnl_ext.c
  mur_multi_rehash.c
  mur_open_files.c
  mur_output_record.c
  mur_output_show.c
  mur_pini_addr_reset.c
  mur_pini_state.c
  mur_process_intrpt_recov.c
  mur_process_seqno_table.c
  mur_process_timequal.c
  mur_process_token_table.c
  mur_put_aimg_rec.c
  mur_read_file.c
# mur_read_file_sp.o   in sr_unix
  mur_rem_jctls.c
  mur_report_error.c
  mur_select_rec.c
  mur_sort_files.c
  mur_token_lookup.c
  mur_tp_resolve_time.c
  mur_validate_checksum.c
  mur_ztp_lookback.c
# murgetlst.o      in  sr_unix
  read_db_files_from_gld.c
# recvpool_init.o      in  sr_unix
  repl_comm.c
  repl_filter.c
# repl_inst_create.o      in  sr_unix
# repl_inst_dump.o      in  sr_unix
# repl_inst_edit.o      in  sr_unix
# repl_ipc_cleanup.o      in  sr_unix
# repl_log.o      in  sr_unix
# repl_log_init.o      in  sr_unix
  repl_tr_good.c
  replic_gbldefs.c
# ss_anal_shdw_file.o      in  sr_unix
# ss_get_block.o      in  sr_unix
# ss_initiate.o      in  sr_unix
# ss_read_block.o      in  sr_unix
# upd_log_init.o      in  sr_unix
  updhelper_end.c
  updhelper_init.c
  updhelper_reader.c
  updhelper_writer.c
  updproc.c
  updproc_end.c
  updproc_get_gblname.c
  updproc_init.c
  updproc_open_files.c
  )

set(GTM_DSE_SRC_C
  dse_adrec.c
  dse_adstar.c
  dse_all.c
  dse_b_dmp.c
  dse_cache.c
  dse_chng_bhead.c
  dse_chng_fhead.c
  dse_chng_rhead.c
# dse_cmd_disallow.o    in sr_unix
  dse_crit.c
# dse_ctrlc_handler.o    in sr_unix
  dse_data.c
  dse_dmp.c
  dse_dmp_fhead.c
  dse_eval.c
  dse_exhaus.c
  dse_exit.c
  dse_f_blk.c
  dse_f_free.c
  dse_f_key.c
  dse_f_reg.c
  dse_fdmp.c
  dse_find_roots.c
  dse_flush.c
  dse_getki.c
# dse_help.o      in sr_unix
  dse_integ.c
  dse_is_blk_free.c
  dse_is_blk_in.c
  dse_ksrch.c
  dse_lm_blk_free.c
  dse_m_rest.c
  dse_maps.c
# dse_open.o      in sr_unix
  dse_order.c
  dse_over.c
  dse_page.c
# dse_puttime.o      in sr_unix
  dse_r_dmp.c
  dse_range.c
# dse_remove.o      in sr_unix
  dse_rest.c
  dse_rmrec.c
  dse_rmsb.c
  dse_save.c
  dse_shift.c
  dse_wcreinit.c
  dump_record.c
  skan_offset.c
  skan_rnum.c
  )

set(GTM_FRAME_SRC_C
  unw_prof_frame_dummy.c
  movtc.c
  )

set(GTM_GNPCLIENT_SRC_C
  # The rest of the sources are in sr_port_cm
  callg_signal.c
  )

set(GTM_PORT_SRC_C_EXTRAS
  caller_id.c                 # There is another caller_id.c in sr_linux
  gtm_threadgbl_deftypes.c    # Not found in manual build log
  )

#
#  Select sources specific for 32 bits
#
if(ARCHITECTURE_IS_32_BITS)
  set(GTM_MUMPS_PORT_SRC_C
    ${GTM_MUMPS_PORT_SRC_C}
    )
endif()



#
#  Select sources specific for 64 bits
#
if(ARCHITECTURE_IS_64_BITS)
  set(GTM_MUMPS_PORT_SRC_C
    ${GTM_MUMPS_PORT_SRC_C}
    bx_boolop.c
    emit_code.c
    job_addr.c
    op_zgoto.c
    code_gen.c
    urx_resolve.c
    shrink_trips.c
    zlput_rname.c
    m_zgoto.c
    )
endif()

set(GTM_LKE_PORT_SRC_C
  lke_clear.c
  lke_clearlock.c
  lke_cleartree.c
  lke_exit.c
# lke_fileio.c    in  sr_unix
# lke_getansw.c   in  sr_unix
  lke_getcli.c
  lke_getki.c
# lke_help.c      in  sr_unix
# lke_setgdr.c    in sr_unix
  lke_show.c
  lke_showlock.c
  lke_showtree.c
  )

add_library(frameport ${LIBRARY_TYPE}
  ${GTM_FRAME_SRC_C}
  )

add_library(gnpclientport ${LIBRARY_TYPE}
  ${GTM_GNPCLIENT_SRC_C}
  )

add_library(dseport ${LIBRARY_TYPE}
  ${GTM_DSE_SRC_C}
  )

add_library(mupipport ${LIBRARY_TYPE}
  ${GTM_MUPIP_PORT_SRC_C}
  )

add_library(mumpsport ${LIBRARY_TYPE}
  ${GTM_MUMPS_PORT_SRC_C}
  )

target_link_libraries(mumpsport
  rt
  )

add_library(lkeport ${LIBRARY_TYPE}
  ${GTM_LKE_PORT_SRC_C}
  )

#
#  Complimentary pieces are in sr_unix
#
add_library(dbcertifyport ${LIBRARY_TYPE}
  dbcertify.c
  dbcertify_base_ch.c
  dbcertify_certify_phase.c
  dbcertify_funcs.c
  dbcertify_scan_phase.c
  )
