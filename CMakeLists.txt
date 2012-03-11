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
  message("This is a 64 bits architecture")
endif()

if(CMAKE_C_SIZEOF_DATA_PTR EQUAL 4)
  message("This is a 32 bits architecture")
endif()


#
# Visit subdirectories
#
add_subdirectory(sr_linux)
# add_subdirectory(sr_unix_nsb)   # no needed when USHBIN is ON
add_subdirectory(sr_unix_cm)
add_subdirectory(sr_unix_gnp)
add_subdirectory(sr_unix)
add_subdirectory(sr_port_cm)
add_subdirectory(sr_port)
add_subdirectory(pro)


#
# Select architecture dependent directories
#
if(CMAKE_C_SIZEOF_DATA_PTR EQUAL 4)
  add_subdirectory(sr_i386)
endif()

if(CMAKE_C_SIZEOF_DATA_PTR EQUAL 8)
  set(LINUX_64)
  add_subdirectory(sr_x86_64)
endif()

