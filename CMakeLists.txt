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

add_subdirectory(sr_linux)
add_subdirectory(sr_i386)
add_subdirectory(sr_unix_nsb)
add_subdirectory(sr_unix_cm)
add_subdirectory(sr_unix_gnp)
add_subdirectory(sr_unix)

# add_subdirectory(sr_port)
# add_subdirectory(sr_port_cm)
# add_subdirectory(sr_unix_gnp)
# add_subdirectory(sr_x86_64)

# sr_linux sr_i386 sr_x86_regs sr_unix_gnp sr_unix_cm sr_unix_nsb sr_unix sr_port_cm sr_port
