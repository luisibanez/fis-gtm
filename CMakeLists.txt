cmake_minimum_required(VERSION 2.8.7)
project(GTM C ASM)

set(CMAKE_INCLUDE_FLAG_ASM "-Wa,-I") # gcc -I does not make it to "as"
set(CMAKE_C_FLAGS
  # TODO: Use CMake 2.8.9 POSITION_INDEPENDENT_CODE abstraction for -fPIC in static libs
  "${CMAKE_C_FLAGS} -ansi -fPIC -fsigned-char -Wmissing-prototypes -Wno-unused-result")
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

set(arch_path)
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
  list(APPEND arch_path sr_linux)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
    list(APPEND arch_path sr_i386 sr_x86_regs sr_unix_nsb)
  else()
    list(APPEND arch_path sr_x86_64 sr_x86_regs)
  endif()
endif()
list(APPEND arch_path
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

function(find_source src_var name)
  set(found "")
  foreach(d ${arch_path})
    if(ARGN)
      foreach(ext ${ARGN})
        set(src "${GTM_SOURCE_DIR}/${d}/${name}${ext}")
        if(EXISTS "${src}")
          set(found "${src}")
          break()
        endif()
      endforeach()
    else()
     set(src "${GTM_SOURCE_DIR}/${d}/${name}")
     if(EXISTS "${src}")
       set(found "${src}")
       break()
     endif()
    endif()
    if(found)
      break()
    endif()
  endforeach()
  if(NOT found)
    message(FATAL_ERROR "Cannot find \"${name}\" as ${ARGN}")
  endif()
  set("${src_var}" "${found}" PARENT_SCOPE)
 endfunction()

function(load_source_list srcs_var listfile)
  set(srcs "")
  file(STRINGS "${listfile}" names)
  foreach(name ${names})
    find_source(src ${name} .c .s .si)
    list(APPEND srcs ${src})
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
 ${GTM_BOOTSTRAP_FILES}/pro/obj/cmierrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/cmerrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/merrors_ctl.c
 ${GTM_BOOTSTRAP_FILES}/pro/obj/gdeerrors_ctl.c
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

add_executable(lke sr_unix/lke.c sr_unix/lke_cmd.c)
target_link_libraries(lke liblke libmumps libgnpclient libmumps libgnpclient libcmisockettcp)

add_executable(gtcm_server sr_unix_cm/gtcm_main.c sr_unix_cm/omi_srvc_xct.c)
target_link_libraries(gtcm_server libgtcm libmumps libstub)
add_executable(gtcm_gnp_server sr_unix_gnp/gtcm_gnp_server.c)
target_link_libraries(gtcm_gnp_server libgnpserver liblke libmumps libcmisockettcp libstub)

#add_custom_command(
#  OUTPUT sr_unix/omi_sx_play.c
#  DEPENDS ${GTM_SOURCE_DIR}/sr_unix_cm/omi_srvc_xct.c
#  COMMAND ${CMAKE_COMMAND} -E copy ${GTM_SOURCE_DIR}/sr_unix_cm/omi_srvc_xct.c
#                                   ${GTM_BINARY_DIR}/sr_unix/omi_sx_play.c
#  )
#add_executable(gtcm_play sr_unix_cm/gtcm_play.c sr_unix/omi_sx_play.c)
add_executable(gtcm_play sr_unix_cm/gtcm_play.c sr_unix_cm/omi_srvc_xct.c)
target_link_libraries(gtcm_play libgtcm libmumps libstub)

add_executable(gtcm_pkdisp sr_unix_cm/gtcm_pkdisp.c)
target_link_libraries(gtcm_pkdisp libgtcm libmumps libstub)
add_executable(gtcm_shmclean sr_unix_cm/gtcm_shmclean.c)
target_link_libraries(gtcm_shmclean libgtcm libmumps libstub)
add_executable(semstat2 sr_unix/semstat2.c)
add_executable(ftok sr_unix/ftok.c)
target_link_libraries(ftok libmumps libstub)

set_property(TARGET ${with_export} PROPERTY LINK_FLAGS
  "-Wl,-u,gtm_filename_to_id -Wl,-u,gtm_zstatus -Wl,--version-script,\"${GTM_SOURCE_DIR}/gtmexe_symbols.export\"")

add_library(libgtmshr SHARED sr_unix/gtm_main.c)
set_property(TARGET libgtmshr PROPERTY OUTPUT_NAME gtmshr)
target_link_libraries(libgtmshr libmumps libgnpclient libcmisockettcp)
set_property(TARGET libgtmshr PROPERTY LINK_FLAGS
  "-Wl,-u,gtm_ci -Wl,-u,gtm_filename_to_id -Wl,--version-script,\"${GTM_SOURCE_DIR}/gtmshr_symbols.export\"")

add_library(libgtmcrypt SHARED
  sr_unix/gtmcrypt_ref.c
  sr_unix/gtmcrypt_pk_ref.c
  sr_unix/gtmcrypt_dbk_ref.c
  )
set_property(TARGET libgtmcrypt PROPERTY OUTPUT_NAME gtmcrypt)
set_property(TARGET libgtmcrypt PROPERTY COMPILE_DEFINITIONS USE_GCRYPT)
target_link_libraries(libgtmcrypt gpg-error gpgme gcrypt)
install(TARGETS libgtmcrypt DESTINATION plugin)

add_executable(maskpass sr_unix/maskpass.c)
target_link_libraries(maskpass gpg-error gpgme gcrypt)
set_property(TARGET maskpass PROPERTY COMPILE_DEFINITIONS USE_GCRYPT)
install(TARGETS maskpass DESTINATION plugin/gtmcrypt)

install(TARGETS
  mumps
  dse
  lke
  gtcm_server
  gtcm_gnp_server
  gtcm_pkdisp
  gtcm_play
  gtcm_shmclean
  semstat2
  ftok
  gtmsecshr
  mupip
  libgtmshr
  DESTINATION .
  )
install(TARGETS gtmsecshr_real DESTINATION gtmsecshrdir)

# <r>.m -> <R>.m
file(GLOB m_files RELATIVE ${GTM_SOURCE_DIR}/sr_port ${GTM_SOURCE_DIR}/sr_port/*.m)
foreach(m ${m_files})
  string(TOUPPER "${m}" m_upper)
  string(REGEX REPLACE "M$" "m" m_out "${m_upper}")
  install(FILES "${GTM_SOURCE_DIR}/sr_port/${m}" DESTINATION . RENAME ${m_out})
endforeach()

# <r>.mpt -> _<R>.m
file(GLOB mpt_files RELATIVE ${GTM_SOURCE_DIR}/sr_port ${GTM_SOURCE_DIR}/sr_port/*.mpt)
foreach(mpt ${mpt_files})
  string(TOUPPER "_${mpt}" mpt_upper)
  string(REGEX REPLACE "MPT$" "m" mpt_out "${mpt_upper}")
  install(FILES "${GTM_SOURCE_DIR}/sr_port/${mpt}" DESTINATION . RENAME ${mpt_out})
endforeach()

set(files)
foreach(f
  gtm_stdio.h
  gtmxc_types.h
  gtm_stdlib.h
  gtm_string.h
  gtm_strings.h
  gtm_limits.h
  main_pragma.h
  arch.gtc
  gtcm_run.gtc
  gtcm_slist.gtc
  configure.gtc
  gdedefaults.gtc
  gtmbase.gtc
  gtmcshrc.gtc
  gtm.gtc
  gtmprofile.gtc
  gtmprofile_preV54000.gtc
  gtmstart.gtc
  gtmstop.gtc
  dse.hlp
  gde.hlp
  lke.hlp
  mumps.hlp
  mupip.hlp
  )
  find_source(src ${f})
  list(APPEND files ${src})
endforeach()
install(FILES ${files} DESTINATION .)

configure_file(sr_unix/gpgagent.tab.in plugin/gpgagent.tab @ONLY)
install(FILES ${GTM_BINARY_DIR}/plugin/gpgagent.tab DESTINATION plugin)

# Would install to:
# /usr/lib/fis-gtm/V5.5-000_x86
# /usr/lib/fis-gtm/V5.5-000_x86_64
