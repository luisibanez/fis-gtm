include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_x86_64
  ${fis-gtm_SOURCE_DIR}/sr_x86_regs
  ${fis-gtm_SOURCE_DIR}/sr_port
# ${fis-gtm_SOURCE_DIR}/sr_unix_nsb  # no needed when USHBIN is ON as it is the case on Linux
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_unix_cm
  ${fis-gtm_SOURCE_DIR}/sr_linux
  )

set(SRC_C
  cmerrors_ctl.c
  cmierrors_ctl.c
  gdeerrors_ctl.c
  merrors_ctl.c
  omi_sx_play.c
  ttt.c
  )

add_library(fisgtmproobj
  ${SRC_C}
  )
