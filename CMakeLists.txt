cmake_minimum_required(VERSION 2.8.7)
project(GTM C)

set(arch_path
  sr_linux
  sr_x86_64 # sr_i386
  sr_x86_regs
  # sr_unix_nsb  # for 32-bit
  sr_unix
  sr_port
  sr_unix_cm
  sr_unix_gnp
  sr_port_cm
  )

set(GTM_BOOTSTRAP_FILES "${GTM_SOURCE_DIR}/fis-gtm-src-extras")
include_directories(${GTM_BOOTSTRAP_FILES}/pro/obj)

set(includes)
foreach(d ${arch_path})
  list(APPEND includes ${GTM_SOURCE_DIR}/${d})
endforeach()
include_directories(${includes})

function(load_source_list srcs_var listfile)
  set(srcs "")
  file(STRINGS "${listfile}" names)
  foreach(name ${names})
    set(found 0)
    foreach(d ${arch_path})
      set(src "${GTM_SOURCE_DIR}/${d}/${name}.c")
      if(EXISTS "${src}")
        list(APPEND srcs "${src}")
        set(found 1)
        break()
      endif()
    endforeach()
    if(NOT found)
      message(FATAL_ERROR "Cannot find ${name}")
    endif()
  endforeach()
  set(${srcs_var} "${srcs}" PARENT_SCOPE)
endfunction()
message("lke_srcs=[${lke_srcs}]")

load_source_list(gtcm_srcs sr_unix_cm/libgtcm.list)
load_source_list(cmisockettcp_srcs sr_unix_gnp/libcmisockettcp.list)
load_source_list(gnpclient_srcs sr_unix_gnp/libgnpclient.list)
load_source_list(gnpserver_srcs sr_unix_gnp/libgnpserver.list)
load_source_list(dbcertify_srcs sr_unix/libdbcertify.list)
load_source_list(dse_srcs sr_unix/libdse.list)
load_source_list(lke_srcs sr_unix/liblke.list)
load_source_list(mupip_srcs sr_unix/libmupip.list)
load_source_list(stub_srcs sr_unix/libstub.list)

foreach(lib
  gtcm
  cmisockettcp
  gnpclient
  gnpserver
  dbcertify
  dse
  lke
  mupip
  stub
  )
  add_library(${lib} STATIC ${${lib}_srcs})
endforeach()
