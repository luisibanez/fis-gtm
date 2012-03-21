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
  ${fis-gtm_SOURCE_DIR}/sr_i386
  ${fis-gtm_SOURCE_DIR}/sr_port_cm
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/pro/obj
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_linux
  )


set(GTM_CMI_SOCKET_TCP_UNIX_SRC_C
  cmi_alloc.c
  cmi_close.c
  cmi_debug.c
  cmi_idle.c
  cmi_init.c
  cmi_open.c
  cmi_peer_info.c
  cmi_read.c
  cmi_write.c
  cmi_write_urg.c
  cmj_async.c
  cmj_clb_async.c
  cmj_err.c
  cmj_exception.c
  cmj_fini.c
  cmj_firstone.c
  cmj_get_port.c
  cmj_getsockaddr.c
  cmj_getdeferred.c
  cmj_handler.c
  cmj_housekeeping.c
  cmj_incoming_call.c
  cmj_init_clb.c
  cmj_netinit.c
  cmj_postevent.c
  cmj_read.c
  cmj_resolve_nod_tnd.c
  cmj_select.c
  cmj_setupfd.c
  cmj_unit2clb.c
  cmj_write.c
  cmu_getclb.c
  cmu_ntdroot.c
  gvcmz_errmsg.c
  gtcm_ch.c
  gtcmd_ini_reg.c
  gtcm_exi_ch.c
  gtcm_gnp_clitab.c
  gtcm_gnp_pktdmp.c
  gtcm_gnp_server.c
  gtcm_open_cmerrlog.c
  gtcm_urgread_ast.c
  )

add_library(cmisockettcp ${LIBRARY_TYPE}
  ${GTM_CMI_SOCKET_TCP_UNIX_SRC_C}
  )

