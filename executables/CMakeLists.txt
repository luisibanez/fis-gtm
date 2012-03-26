
if(ARCHITECTURE_IS_32_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_i386
    ${fis-gtm_SOURCE_DIR}/sr_unix_nsb
    ${fis-gtm_BINARY_DIR}/pro/obj
    ${fis-gtm_SOURCE_DIR}/sr_unix
    ${fis-gtm_SOURCE_DIR}/sr_port
    )
endif()


if(ARCHITECTURE_IS_64_BITS)
  include_directories(
    ${fis-gtm_SOURCE_DIR}/sr_x86_64
    ${fis-gtm_BINARY_DIR}/pro/obj
    ${fis-gtm_SOURCE_DIR}/sr_unix
    ${fis-gtm_SOURCE_DIR}/sr_port
    )
endif()


#
# List of architecture dependent libraries
#
if(ARCHITECTURE_IS_32_BITS)
  set(ARCHITECTURE_DEPENDENT_LIBRARIES
    ${ARCHITECTURE_DEPENDENT_LIBRARIES}
    fisgtmi386
    stubunix
    gtmunixcm 
    cmisockettcp
    frameport
    gtm_unix_nsb
    )
endif()

if(ARCHITECTURE_IS_64_BITS)
  set(ARCHITECTURE_DEPENDENT_LIBRARIES
    ${ARCHITECTURE_DEPENDENT_LIBRARIES}
    fisgtmx64
    gnpclientportcm
    gnpclientport
    cmisockettcpportcm
    cmisockettcp
    gtmportcm
    gtmunixcm
    ftokunix
    frameport
    )
endif()



add_executable(mumps
  ../sr_unix/gtm_main.c
  )

target_link_libraries(mumps
  lkeport
  lkeunix
  fisgtmproobj
  mumpsport
  mumpsunix
  mupipport
  mupipunix
  gtmlinux2
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  ${CURSES_LIBRARIES}
  elf
  dl
  pthread
  m
  )


add_executable(dse
  ../sr_unix/dse.c
  ../sr_unix/lke_cmd.c
  ../sr_unix/lke_ctrlc_handler.c
  )

target_link_libraries(dse
  lkeport
  lkeunix
  mumpsport
  mumpsunix
  mupipport
  mupipunix
  dseport
  dseunix
  gtmlinux2
  gtmportcm
  cmisockettcpportcm
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  ${CURSES_LIBRARIES}
  elf
  dl
  pthread
  m
  )



add_executable(mupip
  ../sr_unix/mupip.c
  )

target_link_libraries(mupip
  mupipport
  mupipunix
  lkeport
  lkeunix
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  mumpsport
  mumpsunix
  mumpsport
  mumpsunix
  gtmlinux2
  fisgtmproobj
  ${CURSES_LIBRARIES}
  elf
  dl
  pthread
  m
  )


add_executable(lke
  ../sr_unix/lke.c
  ../sr_unix/lke_cmd.c
  ../sr_unix/lke_ctrlc_handler.c
  )

target_link_libraries(lke
  lkeport
  lkeunix
  mumpsport
  mumpsunix
  mupipport
  mupipunix
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  fisgtmproobj
  gtmlinux2
  ${CURSES_LIBRARIES}
  elf
  dl
  pthread
  m
  )



add_executable(gtm
  ../sr_unix/gtm.c
  )

target_link_libraries(gtm
  dl
  m
  )



add_executable(semstat2
  ../sr_unix/semstat2.c
  )

target_link_libraries(semstat2
  elf
  dl
  )


add_executable(gtmsecshr
  ../sr_unix/gtmsecshr.c
  )

target_link_libraries(gtmsecshr
  mumpsport
  mumpsunix
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  lkeport
  lkeunix
  gtmlinux2
  mupipport
  mupipunix
  ${CURSES_LIBRARIES}
  pthread
  elf
  dl
  m
  )


add_executable(gtcm_pkdisp
  ../sr_unix_cm/gtcm_pkdisp.c
  )

target_link_libraries(gtcm_pkdisp
  mumpsport
  mumpsunix
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  lkeport
  lkeunix
  gtmlinux2
  mupipport
  mupipunix
  ${CURSES_LIBRARIES}
  pthread
  elf
  dl
  m
  )


add_executable(gtcm_play
  ../sr_unix_cm/gtcm_play.c
  )

target_link_libraries(gtcm_play
  mumpsport
  mumpsunix
  mupipport
  mupipunix
  stubunix
  gtmlinux2
  lkeport
  lkeunix
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  ${CURSES_LIBRARIES}
  pthread
  elf
  dl
  m
  )


add_executable(gtcm_shmclean
  ../sr_unix_cm/gtcm_shmclean.c
  )

target_link_libraries(gtcm_shmclean
  mumpsport
  mumpsunix
  mupipport
  mupipunix
  gtmlinux2
  stubunix
  lkeport
  lkeunix
  fisgtmproobj
  ${ARCHITECTURE_DEPENDENT_LIBRARIES}
  ${CURSES_LIBRARIES}
  pthread
  elf
  dl
  m
  )


