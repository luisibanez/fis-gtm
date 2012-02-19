include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_linux
  )

add_library(gtm_linux
  caller_id.c
  gtm_getenv.c
  gtm_system.c
  inst_flush.c
  )
