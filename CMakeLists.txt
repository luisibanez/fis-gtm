cmake_minimum_required(VERSION 2.8.7)
project(GTM C ASM)
set(CMAKE_INSTALL_PREFIX "${GTM_BINARY_DIR}/stage")

set(CMAKE_INCLUDE_FLAG_ASM "-Wa,-I") # gcc -I does not make it to "as"
set(CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} -ansi -fsigned-char -Wmissing-prototypes -Wno-unused-result")
set(CMAKE_C_FLAGS_RELEASE
  "${CMAKE_C_FLAGS_RELEASE} -fno-defer-pop -fno-strict-aliasing -ffloat-store")
add_definitions(
  #-DNOLIBGTMSHR #gt_cc_option_DBTABLD=-DNOLIBGTMSHR
  -D_GNU_SOURCE
  -D_FILE_OFFSET_BITS=64
  -D_XOPEN_SOURCE=600
  -D_LARGEFILE64_SOURCE
  )
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG DEBUG)

#gt_cc_option_I= -I/usr/local/include -I/usr/include/libelf

# -Wl,-M -rdynamic -Wl,-u

#gt_ld_linker=cc
#gt_ld_option_output=-o
#gt_ld_options_common=-Wl,-M
#gt_ld_options_bta=-Wl,-M
#gt_ld_options_dbg=-Wl,-M
#gt_ld_options_pro=-Wl,-M
#gt_ld_options_gtmshr=-Wl,-u,gtm_filename_to_id -Wl,--version-script,gtmshr_symbols.export
#gt_ld_ci_u_option=-Wl,-u,gtm_ci
#gt_ld_extra_libs=
#gt_ld_syslibs= -lelf -lncurses -lm -ldl -lc -lpthread -lrt
#gt_ld_sysrtns=
#gt_ld_aio_syslib=-lrt
#gt_ld_m_shl_linker=ld
#gt_ld_m_shl_options=-shared
#gt_ld_shl_linker=cc
#gt_ld_shl_suffix=.so
#gt_ld_options_all_exe=-rdynamic -Wl,-u,gtm_filename_to_id -Wl,-u,gtm_zstatus -Wl,--version-script,gtmexe_symbols.export
#gt_ld_shl_options=-shared
#gt_ld_ci_options=-Wl,-u,gtm_ci -Wl,-u,gtm_filename_to_id -Wl,--version-script,gtmshr_symbols.export

# $gt_ld_options_all_exe $gt_ld_syslibs

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
      foreach(ext .c .s .si)
        set(src "${GTM_SOURCE_DIR}/${d}/${name}${ext}")
        if(EXISTS "${src}")
          list(APPEND srcs "${src}")
          set(found 1)
         break()
        endif()
      endforeach()
      if(found)
        break()
      endif()
    endforeach()
    if(NOT found)
      message(FATAL_ERROR "Cannot find ${name}")
    endif()
  endforeach()
  set(${srcs_var} "${srcs}" PARENT_SCOPE)
endfunction()

load_source_list(gtcm_srcs sr_unix_cm/libgtcm.list)
load_source_list(cmisockettcp_srcs sr_unix_gnp/libcmisockettcp.list)
load_source_list(gnpclient_srcs sr_unix_gnp/libgnpclient.list)
load_source_list(gnpserver_srcs sr_unix_gnp/libgnpserver.list)
load_source_list(dbcertify_srcs sr_unix/libdbcertify.list)
load_source_list(dse_srcs sr_unix/libdse.list)
load_source_list(lke_srcs sr_unix/liblke.list)
load_source_list(mupip_srcs sr_unix/libmupip.list)
load_source_list(stub_srcs sr_unix/libstub.list)

#load_source_list(mumps_srcs sr_i386/libmumps.list)
load_source_list(mumps_srcs sr_x86_64/libmumps.list)
# TODO: Load libmumps leftovers automatically
# libmumps has everything not in source lists:
#   *.c *.si *.s
# but excluding names hidden by earlier arch_path entries.
#set(all_srcs "")
#foreach(d ${arch_path})
#  file(GLOB all_srcs RELATIVE ${GTM_SOURCE_DIR}
#    ${GTM_SOURCE_DIR}/${d}/*.c
#    ${GTM_SOURCE_DIR}/${d}/*.si
#    ${GTM_SOURCE_DIR}/${d}/*.s
#    )
#endforeach()

list(APPEND mumps_srcs
 ${GTM_BOOTSTRAP_FILES}/pro/obj/ttt.c
 #${GTM_BOOTSTRAP_FILES}/pro/obj/xfer_desc.i
 ${GTM_BOOTSTRAP_FILES}/pro/obj/cmierrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/cmerrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/merrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/gdeerrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/omi_sx_play.c
)

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
  mumps
  )
  add_library(lib${lib} STATIC ${${lib}_srcs})
  set_property(TARGET lib${lib} PROPERTY OUTPUT_NAME ${lib})
endforeach()

# TODO: find_package or find_library for system libs?
target_link_libraries(libmumps -lelf -lncurses -lm -ldl -lpthread -lrt)

add_executable(mumps sr_unix/gtm.c)
target_link_libraries(mumps libmumps)

#omi_sx_play.c: omi_srvc_xct.c
add_executable(dse sr_unix/dse.c sr_unix/dse_cmd.c)
target_link_libraries(dse libdse libmumps libstub)
list(APPEND with_export dse)

add_executable(geteuid sr_unix/geteuid.c)

add_executable(gtmsecshr sr_unix/gtmsecshr_wrapper.c)

add_executable(gtmsecshr_real sr_unix/gtmsecshr.c)
target_link_libraries(gtmsecshr_real libmumps)
set_target_properties(gtmsecshr_real PROPERTIES
  OUTPUT_NAME gtmsecshr
  RUNTIME_OUTPUT_DIRECTORY ${GTM_BINARY_DIR}/gtmsecshrdir
  )

add_executable(mupip sr_unix/mupip.c sr_unix/mupip_cmd.c)
target_link_libraries(mupip libmupip libmumps libstub)
list(APPEND with_export mupip)

set_property(TARGET ${with_export} PROPERTY LINK_FLAGS
  "-Wl,-u,gtm_filename_to_id -Wl,-u,gtm_zstatus -Wl,--version-script,\"${GTM_SOURCE_DIR}/gtmexe_symbols.export\"")
install(TARGETS
  mumps
  dse
  gtmsecshr
  mupip
  DESTINATION .
  )
install(TARGETS gtmsecshr_real DESTINATION gtmsecshrdir)

# Would install to:
# /usr/lib/fis-gtm/V5.5-000_x86
# /usr/lib/fis-gtm/V5.5-000_x86_64

# gtmshr_obj=gtm_main.o
# lke_obj=lke.o lke_cmd.o
# dse_obj=dse.o dse_cmd.o
# mupip_obj=mupip.o mupip_cmd.o
# dbcertify_obj=dbcertify.o dbcertify_cmd.o
# gtmsecshr_obj=gtmsecshr.o
# gtmsecshr_wrapper_obj=gtmsecshr_wrapper.o
# geteuid_obj=geteuid.o
# semstat2_obj=semstat2.o
# ftok_obj=ftok.o
# gtcm_server_obj=gtcm_main.o omi_srvc_xct.o
# gtcm_gnp_server_obj=gtcm_gnp_server.o
# gtcm_play_obj=gtcm_play.o omi_sx_play.o
# gtcm_pkdisp_obj=gtcm_pkdisp.o
# gtcm_shmclean_obj=gtcm_shmclean.o
# dtgbldir_obj=dtgbldir.o
# dummy_gtmci_obj=dummy_gtmci.o
# ../mumps: $(mumps_obj)
#   $(gt-ld)
# ../dse: $(dse_obj) libdse.a libmumps.a libstub.a
#   $(gt-ld_with_export)
# ../geteuid: $(geteuid_obj) libmumps.a
#   $(gt-ld)
# ../gtmsecshr_real: $(gtmsecshr_obj) libmumps.a
#   $(gt-ld)
# ../gtmsecshr_wrapper: $(gtmsecshr_wrapper_obj) libmumps.a
#   $(gt-ld)
# ../lke: $(lke_obj) liblke.a libmumps.a libgnpclient.a libmumps.a libgnpclient.a libcmisockettcp.a
#   $(gt-ld)
# ../mupip: $(mupip_obj) libmupip.a libmumps.a libstub.a $(gt_ld_aio_syslib)
#   $(gt-ld_with_export)
# ../dbcertify: $(dbcertify_obj) libdbcertify.a libmupip.a libmumps.a libstub.a $(gt_ld_aio_syslib)
#   $(gt-ld)
# ../gtcm_server: $(gtcm_server_obj) libgtcm.a libmumps.a libstub.a
#   $(gt-ld)
# ../gtcm_gnp_server: $(gtcm_gnp_server_obj) libgnpserver.a liblke.a libmumps.a libcmisockettcp.a libstub.a
#   $(gt-ld)
# ../gtcm_play: $(gtcm_play_obj) libgtcm.a libmumps.a libstub.a
#   $(gt-ld)
# ../gtcm_pkdisp: $(gtcm_pkdisp_obj) libgtcm.a libmumps.a libstub.a
#   $(gt-ld)
# ../gtcm_shmclean: $(gtcm_shmclean_obj) libgtcm.a libmumps.a libstub.a
#   $(gt-ld)
# ../semstat2: $(semstat2_obj)
#   $(gt-ld)
# ../ftok: $(ftok_obj) libmumps.a
#   $(gt-ld)
