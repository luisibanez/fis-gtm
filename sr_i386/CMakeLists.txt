if(ARCHITECTURE_IS_32_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_i386
    ${fis-gtm_SOURCE_DIR}/sr_unix_nsb
    ${fis-gtm_BINARY_DIR}/pro/obj
    )
endif()


if(ARCHITECTURE_IS_64_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_x86_64
    ${fis-gtm_BINARY_DIR}/pro/obj
    )
endif()


include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_x86_regs
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_linux
  )


set(SRC_C
  auto_zlink.c
  find_line_call.c
  obj_file.c
  )


if(ARCHITECTURE_IS_64_BITS)
  set(SRC_C ${SRC_C}
  emit_code.c
  incr_link.c
  make_cimode.c
  make_dmode.c
  )
endif()


set(SRC_S
  aswp.s
  call_dm.s
  caller_id.s
  callg.s
  ci_restart.s
  compswap.s
  dm_start.s
  follow.s
  mint2mval.s
  mum_tstart.s
  mval2bool.s
  mval2mint.s
  mval2num.s
  op_bkpt.s
  op_call.s
  op_callsp.s
  op_contain.s
  op_currtn.s
  op_equnul.s
  op_equ.s
  op_exfun.s
  op_extcall.s
  op_extexfun.s
  op_extjmp.s
  op_fetchintrrpt.s
  op_fnget.s
  op_fnzextract.s
  op_follow.s
  op_forcenum.s
  op_forchk1.s
  op_forinit.s
  op_forintrrpt.s
  op_forlcldo.s
  op_forloop.s
  op_gettruth.s
  op_iretmvad.s
# op_isformal.s    not in version 5.5
  op_linefetch.s
  op_linestart.s
  op_mprofcall.s
  op_mprofcallsp.s
  op_mprofexfun.s
  op_mprofextcall.s
  op_mprofextexfun.s
  op_mprofforchk1.s
  op_mprofforlcldo.s
  op_mproflinefetch.s
  op_mproflinestart.s
  op_neg.s
  op_numcmp.s
  op_pattern.s
  opp_break.s
  opp_commarg.s
  opp_dmode.s
  opp_hardret.s
  opp_inddevparms.s
  opp_indfnname.s
  opp_indfun.s
  opp_indget.s
  opp_indglvn.s
  opp_indincr.s
  opp_indlvadr.s
  opp_indlvarg.s
  opp_indlvnamadr.s
  opp_indmerge.s
  opp_indo2.s
  opp_indpat.s
  opp_indrzshow.s
  opp_indset.s
  opp_indtext.s
  opp_iretmval.s
  opp_newintrinsic.s
  opp_newvar.s
  opp_ret.s
  opp_rterror.s
  opp_svput.s
  opp_tcommit.s
  opp_trestart.s
  opp_trollback.s
  opp_tstart.s
  opp_xnew.s
  opp_zcont.s
  opp_zg1.s
  opp_zgoto.s
  op_restartpc.s
  op_retarg.s
  op_sorts_after.s
  op_startintrrpt.s
  op_sto.s
  op_zhelp.s
  pseudo_ret.s
# zl_lab_err.s   not in version 5.5
  )


add_library(fisgtmi386 ${LIBRARY_TYPE}
  ${SRC_C}
  ${SRC_S}
  )
