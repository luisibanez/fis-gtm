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
  ${fis-gtm_SOURCE_DIR}/sr_x86_regs
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/sr_unix
  ${fis-gtm_SOURCE_DIR}/sr_unix_cm
  ${fis-gtm_SOURCE_DIR}/sr_linux
  )

set(GTM_MUMPS_PRO_SRC_C
  ttt.c
  )

add_library(mumpspro ${LIBRARY_TYPE}
  ${GTM_MUMPS_PRO_SRC_C}
  )

set(SRC_C
  cmerrors_ctl.c
  cmierrors_ctl.c
  gdeerrors_ctl.c
  merrors_ctl.c
  omi_sx_play.c
  ttt.c
  )

add_library(fisgtmproobj ${LIBRARY_TYPE}
  ${SRC_C}
  )
