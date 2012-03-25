if(ARCHITECTURE_IS_32_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_i386
    ${fis-gtm_SOURCE_DIR}/sr_unix_nsb
    )
endif()


if(ARCHITECTURE_IS_64_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_x86_64
    )
endif()


include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/pro
  ${fis-gtm_SOURCE_DIR}/pro/obj
  ${fis-gtm_SOURCE_DIR}/sr_port_cm
  ${fis-gtm_SOURCE_DIR}/sr_port
  )

set(GTM_PORT_CM_SRC_C
  gtcm_action_pending.c
  gtcm_add_region.c
  gtcm_bind_name.c
  gtcm_exi_handler.c
  gtcm_find_proc.c
  gtcm_find_reghead.c
  gtcm_find_region.c
  gtcm_init_ast.c
  gtcm_int_unpack.c
  gtcm_jnl_switched.c
  gtcm_link_accept.c
  gtcm_neterr.c
  gtcm_read_ast.c
  gtcm_remove_from_action_queue.c
  gtcm_shutdown_ast.c
  gtcm_write_ast.c
  gtcmd_cst_init.c
  gtcmd_rundown.c
  gtcml_blklck.c
  gtcml_chklck.c
  gtcml_chkprc.c
  gtcml_chkreg.c
  gtcml_decrlock.c
  gtcml_dolock.c
  gtcml_incrlock.c
  gtcml_lckclr.c
  gtcml_lcktime.c
  gtcml_lkbckout.c
  gtcml_lkcancel.c
  gtcml_lkhold.c
  gtcml_lklist.c
  gtcml_lkrundown.c
  gtcml_lkstarve.c
  gtcml_lock.c
  gtcml_lock_internal.c
  gtcml_unlock.c
  gtcml_zallocate.c
  gtcml_zdeallocate.c
  gtcmtr_bufflush.c
  gtcmtr_data.c
  gtcmtr_get.c
  gtcmtr_increment.c
  gtcmtr_initproc.c
  gtcmtr_initreg.c
  gtcmtr_kill.c
  gtcmtr_lkacquire.c
  gtcmtr_lkcanall.c
  gtcmtr_lkcancel.c
  gtcmtr_lkdelete.c
  gtcmtr_lke_clearrep.c
  gtcmtr_lke_showrep.c
  gtcmtr_lkreqimmed.c
  gtcmtr_lkreqnode.c
  gtcmtr_lkrequest.c
  gtcmtr_lkresume.c
  gtcmtr_lksuspend.c
  gtcmtr_order.c
  gtcmtr_put.c
  gtcmtr_query.c
  gtcmtr_terminate.c
  gtcmtr_terminate_free.c
  gtcmtr_zprevious.c
  gtcmtr_zwithdraw.c
  )

add_library(gtmportcm ${LIBRARY_TYPE}
  ${GTM_PORT_CM_SRC_C}
  )

set(GTM_GNPCLIENT_PORT_CM_SRC_C
  gtcmtr_lke_clearreq.c
  gtcmtr_lke_showreq.c
  gvcmx_canremlk.c
  gvcmx_data.c
  gvcmx_get.c
  gvcmx_increment.c
  gvcmx_kill.c
  gvcmx_order.c
  gvcmx_put.c
  gvcmx_query.c
  gvcmx_reqremlk.c
  gvcmx_resremlk.c
  gvcmx_susremlk.c
  gvcmx_unlock.c
  gvcmx_zprevious.c
  gvcmy_close.c
  gvcmy_open.c
  gvcmy_open_ch.c
  gvcmy_remlkmgr.c
  gvcmy_rundown.c
  gvcmz_bunch.c
  gvcmz_clrlkreq.c
  gvcmz_doop.c
  gvcmz_error.c
  gvcmz_int_lkcancel.c
  gvcmz_lkacquire_ast.c
  gvcmz_lkcancel_ast.c
  gvcmz_lkread_ast.c
  gvcmz_lksublist.c
  gvcmz_lksuspend_ast.c
  gvcmz_neterr.c
  gvcmz_neterr_set.c
  gvcmz_netopen.c
  gvcmz_sndlkremove.c
  gvcmz_zdef_ast.c
  gvcmz_zflush.c
  lock_cmtimeout.c
  )

add_library(gnpclientportcm ${LIBRARY_TYPE}
  ${GTM_GNPCLIENT_PORT_CM_SRC_C}
  )

set(GTM_CMI_SOCKET_TCP_PORT_CM_SRC_C
  gtcm_err_compat.c
  gtcm_is_query_queryget.c
  gtcm_protocol.c
  gtcm_release_name.c
  )

add_library(cmisockettcpportcm ${LIBRARY_TYPE}
  ${GTM_CMI_SOCKET_TCP_PORT_CM_SRC_C}
  )

