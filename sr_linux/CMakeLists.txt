include_directories(
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_linux
  ${fis-gtm_BINARY_DIR}/pro/obj
  )

add_library(gtmlinux ${LIBRARY_TYPE}
  gtm_getenv.c
  gtm_system.c
  )

add_library(gtmlinux2 ${LIBRARY_TYPE}
  caller_id.c
  inst_flush.c
  )
