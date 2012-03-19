cmake_minimum_required(VERSION 2.8)

project(fis-gtm)

set(LIBRARY_OUTPUT_PATH ${fis-gtm_BINARY_DIR}/lib)

option(USE_GCRYPT  "Use the gcrypt library for encryption" ON)
option(USE_OPENSSL "Use the openssl library for encryption" OFF)

configure_file(
  ${fis-gtm_SOURCE_DIR}/gtmconfig.h.in
  ${fis-gtm_BINARY_DIR}/gtmconfig.h
  )

include_directories(
  ${fis-gtm_BINARY_DIR}
  )


include(CTest)


#
#  Look at the type of architecture.
#

if(CMAKE_C_SIZEOF_DATA_PTR EQUAL 8)
  set(ARCHITECTURE_IS_64_BITS ON)
endif()

if(CMAKE_C_SIZEOF_DATA_PTR EQUAL 4)
  set(ARCHITECTURE_IS_32_BITS ON)
endif()


#
#  Relocate files that were pre-configured with GTM
#
set(FIS_GTM_PRECONFIGURED_SRC_DIR ${fis-gtm_SOURCE_DIR}/fis-gtm-src-extras)
set(FIS_GTM_PRECONFIGURED_DST_DIR ${fis-gtm_BINARY_DIR})

macro(install_gtm_preconfigured subdir filename)
configure_file(
  ${FIS_GTM_PRECONFIGURED_SRC_DIR}/${subdir}/${filename}
  ${FIS_GTM_PRECONFIGURED_DST_DIR}/${subdir}/${filename}
  )
endmacro()

install_gtm_preconfigured("" "setupenv.sh")

install_gtm_preconfigured("sr_linux" "gtm_threadgbl_deftypes.h")

install_gtm_preconfigured("pro" "gtm_limits.h")
install_gtm_preconfigured("pro" "gtm_stdio.h")
install_gtm_preconfigured("pro" "gtm_stdlib.h")
install_gtm_preconfigured("pro" "gtm_string.h")
install_gtm_preconfigured("pro" "gtm_strings.h")
install_gtm_preconfigured("pro" "gtmxc_types.h")
install_gtm_preconfigured("pro" "main_pragma.h")

install_gtm_preconfigured("pro/obj" "ttt.c")
install_gtm_preconfigured("pro/obj" "xfer_desc.i")
install_gtm_preconfigured("pro/obj" "cmierrors_ctl.c")
install_gtm_preconfigured("pro/obj" "cmerrors_ctl.c")
install_gtm_preconfigured("pro/obj" "merrors_ctl.c")
install_gtm_preconfigured("pro/obj" "gdeerrors_ctl.c")
install_gtm_preconfigured("pro/obj" "omi_sx_play.c")
install_gtm_preconfigured("pro/obj" "merrors_ansi.h")
install_gtm_preconfigured("pro/obj" "gtm_threadgbl_deftypes.h")

install_gtm_preconfigured("pro/utf8" "gtmxc_types.h")
install_gtm_preconfigured("pro/utf8" "main_pragma.h")
install_gtm_preconfigured("pro/utf8" "gtm_stdlib.h")
install_gtm_preconfigured("pro/utf8" "gtm_strings.h")
install_gtm_preconfigured("pro/utf8" "gtm_string.h")
install_gtm_preconfigured("pro/utf8" "gtm_stdio.h")
install_gtm_preconfigured("pro/utf8" "gtm_limits.h")

install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_dbk_ref.c")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_dbk_ref.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_interface.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_pk_ref.c")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_pk_ref.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_ref.c")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_ref.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmcrypt_sym_ref.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "gtmxc_types.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "main_pragma.h")
install_gtm_preconfigured("pro/plugin/gtmcrypt" "maskpass.c")


#
#  And add these directories to the header search path
#
include_directories(
  ${fis-gtm_BINARY_DIR}/pro
  ${fis-gtm_BINARY_DIR}/pro/obj
  ${fis-gtm_BINARY_DIR}/pro/utf8
  ${fis-gtm_SOURCE_DIR}/sr_port
  ${fis-gtm_SOURCE_DIR}/sr_unix
  )


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



#
# Visit subdirectories
#
add_subdirectory(sr_linux)
add_subdirectory(sr_unix_cm)
add_subdirectory(sr_unix_gnp)
add_subdirectory(sr_unix)
add_subdirectory(sr_port_cm)
add_subdirectory(sr_port)
add_subdirectory(pro)


#
# Select architecture dependent directories
#
if(ARCHITECTURE_IS_32_BITS)
  add_subdirectory(sr_i386)
endif()

if(ARCHITECTURE_IS_64_BITS)
  add_subdirectory(sr_x86_64)
endif()


#if(EXECUTABLES_READY)

add_executable(dse
  sr_unix/lke.c
  sr_unix/lke_cmd.c
  sr_unix/lke_ctrlc_handler.c
  )

target_link_libraries(dse
#  dseunix
#  dseport
  lkeport
  fisgtmproobj
  fisgtmx64
  mumpsport
  mumpsunix
  elf
  dl
  )

# endif()
