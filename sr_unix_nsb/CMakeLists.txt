include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_i386
  ${fis-gtm_SOURCE_DIR}/sr_port_cm
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/pro/obj
  ${fis-gtm_SOURCE_DIR}/sr_unix_nsb
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_linux
  ${fis-gtm_SOURCE_DIR}/sr_x86_64
  )

set(GTM_UNIX_NSB_SRC
  comp_lits.c
  m_do.c
  obj_code.c
  resolve_ref.c
  shrink_jmps.c
  )

add_library(gtm_unix_nsb
  ${GTM_UNIX_NSB_SRC}
  )

