# CMake 2.8.4 introduced LINK_DEPENDS target property
# CMake 2.8.4 introduced generator expressions in custom commands
# CMake 2.8.5 introduced use of C compiler as the assembler
cmake_minimum_required(VERSION 2.8.5)
project(GTM C ASM)

set(version V5.5-000)
if("${CMAKE_SIZEOF_VOID_P}" EQUAL 4)
  set(arch "x86")
else()
  set(arch "x86_64")
endif()

set(GTM_INSTALL_DIR lib/fis-gtm/${version}_${arch} CACHE STRING "Install directory (under CMAKE_PREFIX_PATH if relative)")
if(NOT GTM_INSTALL_DIR)
  set(GTM_INSTALL_DIR .)
endif()

# Max optimization level is -O2
get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)
foreach(lang ${languages})
  get_property(flags CACHE CMAKE_${lang}_FLAGS_RELEASE PROPERTY VALUE)
  if("${flags}" MATCHES "-O[3-9]")
    string(REGEX REPLACE "-O[3-9]" "-O2" flags "${flags}")
    set_property(CACHE CMAKE_${lang}_FLAGS_RELEASE PROPERTY VALUE "${flags}")
  endif()
endforeach()

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_INCLUDE_FLAG_ASM "-Wa,-I") # gcc -I does not make it to "as"
set(CMAKE_C_FLAGS
  # TODO: Use CMake 2.8.9 POSITION_INDEPENDENT_CODE abstraction for -fPIC in static libs
  "${CMAKE_C_FLAGS} -ansi -fsigned-char -fPIC -Wmissing-prototypes")
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
  sr_unix_gnp
  sr_unix_cm
  sr_unix
  sr_port_cm
  sr_port
  )

set(includes)
foreach(d ${arch_path})
  list(APPEND includes ${GTM_SOURCE_DIR}/${d})
endforeach()
include_directories(${includes})
include_directories(${GTM_BINARY_DIR})

function(select_file src_var name)
  set(found "")
  foreach(d ${arch_path})
    set(src "${GTM_SOURCE_DIR}/${d}/${name}")
    if(EXISTS "${src}")
      set(found "${src}")
      break()
    endif()
  endforeach()
  if(NOT found)
    message(FATAL_ERROR "Cannot find \"${name}\" as ${ARGN}")
  endif()
  set("${src_var}" "${found}" PARENT_SCOPE)
endfunction()

foreach(d ${arch_path})
  file(GLOB sources_${d} RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${d}
    ${d}/*.c ${d}/*.s ${d}/*.si)
endforeach()

macro(set_source_list target)
  foreach(name ${ARGN})
    set(src "")
    foreach(d ${arch_path})
      if(";${sources_${d}};" MATCHES ";(${name}\\.(c|s|si));")
	set(src ${d}/${CMAKE_MATCH_1})
	set("source_used_${CMAKE_MATCH_1}" 1)
	break()
      endif()
    endforeach()
    if(src)
      list(APPEND ${target}_SOURCES ${src})
    else()
      message(FATAL_ERROR "No source \"${name}\" available!")
    endif()
  endforeach()
endmacro()

macro(load_source_list target listfile)
  file(STRINGS "${listfile}" names)
  set_source_list(${target} ${names})
endmacro()

#-----------------------------------------------------------------------------

load_source_list(libcmisockettcp sr_unix_gnp/libcmisockettcp.list)
load_source_list(libdbcertify    sr_unix/libdbcertify.list)
load_source_list(libdse          sr_unix/libdse.list)
load_source_list(libgnpclient    sr_unix_gnp/libgnpclient.list)
load_source_list(libgnpserver    sr_unix_gnp/libgnpserver.list)
load_source_list(libgtcm         sr_unix_cm/libgtcm.list)
load_source_list(liblke          sr_unix/liblke.list)
load_source_list(libmupip        sr_unix/libmupip.list)
load_source_list(libstub         sr_unix/libstub.list)

set_source_list(gtm_threadgbl_deftypes gtm_threadgbl_deftypes)

set_source_list(dbcertify        dbcertify dbcertify_cmd)
set_source_list(dse              dse dse_cmd)
set_source_list(ftok             ftok)
set_source_list(geteuid          geteuid)
set_source_list(gtcm_gnp_server  gtcm_gnp_server)
set_source_list(gtcm_pkdisp      gtcm_pkdisp)
set_source_list(gtcm_play        gtcm_play omi_srvc_xct)
set_source_list(gtcm_server      gtcm_main omi_srvc_xct)
set_source_list(gtcm_shmclean    gtcm_shmclean)
set_source_list(gtmsecshr        gtmsecshr_wrapper)
set_source_list(gtmsecshr_real   gtmsecshr)
set_source_list(libgtmcrypt      gtmcrypt_ref gtmcrypt_pk_ref gtmcrypt_dbk_ref)
set_source_list(libgtmshr        gtm_main)
set_source_list(lke              lke lke_cmd)
set_source_list(maskpass         maskpass)
set_source_list(mumps            gtm)
set_source_list(mupip            mupip mupip_cmd)
set_source_list(semstat2         semstat2)

#-----------------------------------------------------------------------------
# libmumps gets leftover sources, so compute the remaining list.
set(libmumps_SOURCES "")
foreach(d ${arch_path})
  foreach(s ${sources_${d}})
    if(NOT source_used_${s})
      list(APPEND libmumps_SOURCES ${d}/${s})
      set(source_used_${s} 1)
    endif()
  endforeach()
endforeach()
# Remove unused sources.
list(REMOVE_ITEM libmumps_SOURCES
  sr_unix/dtgbldir.c
  )

#-----------------------------------------------------------------------------

add_executable(gtm_threadgbl_deftypes ${gtm_threadgbl_deftypes_SOURCES})

add_custom_command(
  OUTPUT gtm_threadgbl_deftypes.h
  DEPENDS gtm_threadgbl_deftypes
  COMMAND gtm_threadgbl_deftypes > gtm_threadgbl_deftypes.h.tmp
  COMMAND ${CMAKE_COMMAND} -E rename gtm_threadgbl_deftypes.h.tmp gtm_threadgbl_deftypes.h
  )
add_custom_target(gen_gtm_threadgbl_deftypes DEPENDS gtm_threadgbl_deftypes.h)

foreach(exp exe shr)
  set(out gtm${exp}_symbols.export)
  set(in ${GTM_SOURCE_DIR}/sr_unix/gtm${exp}_symbols.exp)
  add_custom_command(
    OUTPUT ${out}
    DEPENDS ${in}
    COMMAND tcsh -f ${GTM_SOURCE_DIR}/sr_linux/genexport.csh ${in} ${out}
    )
endforeach()

add_custom_target(gen_export DEPENDS gtmexe_symbols.export gtmshr_symbols.export)

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
  add_library(lib${lib} STATIC ${lib${lib}_SOURCES})
  set_property(TARGET lib${lib} PROPERTY OUTPUT_NAME ${lib})
  add_dependencies(lib${lib} gen_gtm_threadgbl_deftypes)
endforeach()

# TODO: find_package or find_library for system libs?
target_link_libraries(libmumps -lelf -lncurses -lm -ldl -lpthread -lrt)

add_executable(mumps ${mumps_SOURCES})
target_link_libraries(mumps libmumps)

add_executable(dse ${dse_SOURCES})
target_link_libraries(dse libdse libmumps libstub)
list(APPEND with_export dse)

add_executable(dbcertify ${dbcertify_SOURCES})
target_link_libraries(dbcertify libdbcertify libmupip libmumps libstub)

add_executable(geteuid ${geteuid_SOURCES})

add_executable(gtmsecshr ${gtmsecshr_SOURCES})
add_dependencies(gtmsecshr gen_gtm_threadgbl_deftypes)

add_executable(gtmsecshr_real ${gtmsecshr_real_SOURCES})
target_link_libraries(gtmsecshr_real libmumps)
set_target_properties(gtmsecshr_real PROPERTIES
  OUTPUT_NAME gtmsecshr
  RUNTIME_OUTPUT_DIRECTORY ${GTM_BINARY_DIR}/gtmsecshrdir
  )
add_dependencies(gtmsecshr_real gen_gtm_threadgbl_deftypes)

add_executable(mupip ${mupip_SOURCES})
target_link_libraries(mupip libmupip libmumps libstub)
list(APPEND with_export mupip)

add_executable(lke ${lke_SOURCES})
target_link_libraries(lke liblke libmumps libgnpclient libmumps libgnpclient libcmisockettcp)

add_executable(gtcm_server ${gtcm_server_SOURCES})
target_link_libraries(gtcm_server libgtcm libmumps libstub)
add_executable(gtcm_gnp_server ${gtcm_gnp_server_SOURCES})
target_link_libraries(gtcm_gnp_server libgnpserver liblke libmumps libcmisockettcp libstub)

add_executable(gtcm_play ${gtcm_play_SOURCES})
target_link_libraries(gtcm_play libgtcm libmumps libstub)

add_executable(gtcm_pkdisp ${gtcm_pkdisp_SOURCES})
target_link_libraries(gtcm_pkdisp libgtcm libmumps libstub)
add_executable(gtcm_shmclean ${gtcm_shmclean_SOURCES})
target_link_libraries(gtcm_shmclean libgtcm libmumps libstub)
add_executable(semstat2 ${semstat2_SOURCES})
add_executable(ftok ${ftok_SOURCES})
target_link_libraries(ftok libmumps libstub)

foreach(t ${with_export})
  set_target_properties(${t} PROPERTIES
    LINK_FLAGS "-Wl,-u,gtm_filename_to_id -Wl,-u,gtm_zstatus -Wl,--version-script,\"${GTM_BINARY_DIR}/gtmexe_symbols.export\""
    LINK_DEPENDS "${GTM_BINARY_DIR}/gtmexe_symbols.export"
    )
  add_dependencies(${t} gen_export)
endforeach()

add_library(libgtmshr MODULE ${libgtmshr_SOURCES})
set_property(TARGET libgtmshr PROPERTY OUTPUT_NAME gtmshr)
target_link_libraries(libgtmshr libmumps libgnpclient libcmisockettcp)
set_target_properties(libgtmshr PROPERTIES
  LINK_FLAGS "-Wl,-u,gtm_ci -Wl,-u,gtm_filename_to_id -Wl,--version-script,\"${GTM_BINARY_DIR}/gtmshr_symbols.export\""
  LINK_DEPENDS "${GTM_BINARY_DIR}/gtmshr_symbols.export"
  )
add_dependencies(libgtmshr gen_export)
add_dependencies(mumps libgtmshr)

add_library(libgtmcrypt MODULE ${libgtmcrypt_SOURCES})
set_target_properties(libgtmcrypt PROPERTIES
  OUTPUT_NAME gtmcrypt
  COMPILE_DEFINITIONS USE_GCRYPT
  LIBRARY_OUTPUT_DIRECTORY ${GTM_BINARY_DIR}/plugin
  )
target_link_libraries(libgtmcrypt gpg-error gpgme gcrypt)
install(TARGETS libgtmcrypt DESTINATION ${GTM_INSTALL_DIR}/plugin)

add_executable(maskpass ${maskpass_SOURCES})
target_link_libraries(maskpass gpg-error gpgme gcrypt)
set_target_properties(maskpass PROPERTIES
  COMPILE_DEFINITIONS USE_GCRYPT
  RUNTIME_OUTPUT_DIRECTORY ${GTM_BINARY_DIR}/plugin/gtmcrypt
  )
install(TARGETS maskpass DESTINATION ${GTM_INSTALL_DIR}/plugin/gtmcrypt)

foreach(f
    add_db_key.sh
    build.sh
    encrypt_sign_db_key.sh
    gen_keypair.sh
    gen_sym_hash.sh
    gen_sym_key.sh
    gtmcrypt_dbk_ref.c
    gtmcrypt_pk_ref.c
    gtmcrypt_ref.c
    gtminstall.sh
    import_and_sign_key.sh
    install.sh
    maskpass.c
    pinentry-gtm.sh
    )
  set(f_in "${GTM_SOURCE_DIR}/sr_unix/${f}")
  set(f_out "${GTM_BINARY_DIR}/plugin/gtmcrypt/${f}")
  add_custom_command(
    OUTPUT "${f_out}"
    DEPENDS "${f_in}"
    COMMAND ${CMAKE_COMMAND} -E copy "${f_in}" "${f_out}"
    )
  install(FILES "${f_out}" DESTINATION ${GTM_INSTALL_DIR}/plugin/gtmcrypt)
  list(APPEND files_to_place "${f_out}")
endforeach()

install(TARGETS
  mumps
  dbcertify
  dse
  lke
  geteuid
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
  DESTINATION ${GTM_INSTALL_DIR}
  )
install(TARGETS gtmsecshr_real DESTINATION ${GTM_INSTALL_DIR}/gtmsecshrdir)

# <r>.m -> <R>.m
#file(GLOB m_files_port RELATIVE ${GTM_SOURCE_DIR}/sr_port ${GTM_SOURCE_DIR}/sr_port/*.m)
set(m_files_port
  gde.m
  gdeadd.m
  gdechang.m
  gdedelet.m
  gdeexit.m
  gdehelp.m
  gdeinit.m
  gdelocks.m
  gdelog.m
  gdemap.m
  gdemsgin.m
  gdeparse.m
  gdequit.m
  gderenam.m
  gdescan.m
  gdesetgd.m
  gdeshow.m
  gdespawn.m
  gdetempl.m
  )

foreach(m ${m_files_port})
  string(TOUPPER "${m}" m_upper)
  string(REGEX REPLACE "M$" "m" m_out "${GTM_BINARY_DIR}/${m_upper}")
  add_custom_command(
    OUTPUT "${m_out}"
    DEPENDS ${GTM_SOURCE_DIR}/sr_port/${m}
    COMMAND ${CMAKE_COMMAND} -E copy ${GTM_SOURCE_DIR}/sr_port/${m} "${m_out}"
    )
  install(FILES "${m_out}" DESTINATION ${GTM_INSTALL_DIR})
  list(APPEND files_to_place "${m_out}")
endforeach()

file(GLOB m_files_unix RELATIVE ${GTM_SOURCE_DIR}/sr_unix ${GTM_SOURCE_DIR}/sr_unix/*.m)
foreach(m ${m_files_unix})
  string(TOUPPER "${m}" m_upper)
  string(REGEX REPLACE "M$" "m" m_out "${GTM_BINARY_DIR}/${m_upper}")
  add_custom_command(
    OUTPUT "${m_out}"
    DEPENDS ${GTM_SOURCE_DIR}/sr_unix/${m}
    COMMAND ${CMAKE_COMMAND} -E copy ${GTM_SOURCE_DIR}/sr_unix/${m} "${m_out}"
    )
  install(FILES "${m_out}" DESTINATION ${GTM_INSTALL_DIR})
  list(APPEND files_to_place "${m_out}")
endforeach()

# <r>.mpt -> _<R>.m
file(GLOB mpt_files_port RELATIVE ${GTM_SOURCE_DIR}/sr_port ${GTM_SOURCE_DIR}/sr_port/*.mpt)
foreach(m ${mpt_files_port})
  string(TOUPPER "_${m}" m_upper)
  string(REGEX REPLACE "MPT$" "m" m_out "${GTM_BINARY_DIR}/${m_upper}")
  add_custom_command(
    OUTPUT "${m_out}"
    DEPENDS ${GTM_SOURCE_DIR}/sr_port/${m}
    COMMAND ${CMAKE_COMMAND} -E copy ${GTM_SOURCE_DIR}/sr_port/${m} "${m_out}"
    )
  install(FILES "${m_out}" DESTINATION ${GTM_INSTALL_DIR})
  list(APPEND files_to_place "${m_out}")
endforeach()

file(GLOB mpt_files_unix RELATIVE ${GTM_SOURCE_DIR}/sr_unix ${GTM_SOURCE_DIR}/sr_unix/*.mpt)
foreach(m ${mpt_files_unix})
  string(TOUPPER "_${m}" m_upper)
  string(REGEX REPLACE "MPT$" "m" m_out "${GTM_BINARY_DIR}/${m_upper}")
  add_custom_command(
    OUTPUT "${m_out}"
    DEPENDS ${GTM_SOURCE_DIR}/sr_unix/${m}
    COMMAND ${CMAKE_COMMAND} -E copy ${GTM_SOURCE_DIR}/sr_unix/${m} "${m_out}"
    )
  install(FILES "${m_out}" DESTINATION ${GTM_INSTALL_DIR})
  list(APPEND files_to_place "${m_out}")
endforeach()

set(files)
foreach(f
  gtm_descript.h
  gtm_limits.h
  gtm_sizeof.h
  gtm_stdio.h
  gtm_stdlib.h
  gtm_string.h
  gtm_strings.h
  gtmxc_types.h
  main_pragma.h
  arch.gtc
  gtcm_run.gtc
  gtcm_slist.gtc
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
  select_file(src ${f})
  list(APPEND files ${src})
endforeach()
install(FILES ${files} DESTINATION ${GTM_INSTALL_DIR})

set(GTM_TOP "${GTM_BINARY_DIR}")
configure_file(sr_unix/gpgagent.tab.in plugin/gpgagent.tab @ONLY)
set(GTM_TOP "${CMAKE_INSTALL_PREFIX}/${GTM_INSTALL_DIR}")
configure_file(sr_unix/gpgagent.tab.in CMakeFiles/plugin/gpgagent.tab @ONLY)
install(FILES ${GTM_BINARY_DIR}/CMakeFiles/plugin/gpgagent.tab DESTINATION ${GTM_INSTALL_DIR}/plugin)

install(FILES sr_unix/configure.gtc DESTINATION ${GTM_INSTALL_DIR}
  PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
              GROUP_READ GROUP_EXECUTE
              WORLD_READ WORLD_EXECUTE
  RENAME configure
  )

install(FILES sr_unix/gtminstall.sh DESTINATION ${GTM_INSTALL_DIR}
  PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
              GROUP_READ GROUP_EXECUTE
              WORLD_READ WORLD_EXECUTE
  RENAME gtminstall
  )

install(FILES sr_unix/lowerc_cp.sh DESTINATION ${GTM_INSTALL_DIR}
  PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
              GROUP_READ GROUP_EXECUTE
              WORLD_READ WORLD_EXECUTE
  RENAME lowerc_cp
  )

install(FILES COPYING DESTINATION ${GTM_INSTALL_DIR})

add_custom_target(place_files ALL DEPENDS ${files_to_place})

#-----------------------------------------------------------------------------
# Generate files depending on gtm

# Copy generation routines to a working directory.
foreach(m chk2lev.m chkop.m gendash.m genout.m loadop.m loadvx.m msg.m tttgen.m tttscan.m)
  add_custom_command(
    OUTPUT gen/${m}
    DEPENDS ${GTM_SOURCE_DIR}/sr_port/${m}
    COMMAND ${CMAKE_COMMAND} -E copy ${GTM_SOURCE_DIR}/sr_port/${m} ${GTM_BINARY_DIR}/gen/${m}
    )
endforeach()

add_custom_command(
  OUTPUT gen/ttt.c
  DEPENDS ${GTM_SOURCE_DIR}/sr_unix/ttt.txt
    gen/chk2lev.m gen/chkop.m gen/gendash.m gen/genout.m gen/loadop.m
    gen/loadvx.m gen/tttgen.m gen/tttscan.m ${GTM_SOURCE_DIR}/sr_port/tttgen.cmake
  WORKING_DIRECTORY ${GTM_BINARY_DIR}/gen
  COMMAND ${CMAKE_COMMAND}
  -D gtm_dist=${GTM_BINARY_DIR}
  -D mumps=$<TARGET_FILE:mumps>
  -D sr_port=${GTM_SOURCE_DIR}/sr_port
  -D input=${GTM_SOURCE_DIR}/sr_unix/ttt.txt
  -P ${GTM_SOURCE_DIR}/sr_port/tttgen.cmake
  )
list(APPEND gen_bootstrap_files gen/ttt.c)

foreach(msg
    sr_port/cmerrors.msg
    sr_port/gdeerrors.msg
    sr_port/merrors.msg
    sr_unix_gnp/cmierrors.msg
    )
  get_filename_component(name ${msg} NAME_WE)
  add_custom_command(
    OUTPUT gen/${name}_ctl.c
    DEPENDS gen/msg.m ${GTM_SOURCE_DIR}/${msg} ${GTM_SOURCE_DIR}/sr_port/msg.cmake
    WORKING_DIRECTORY ${GTM_BINARY_DIR}/gen
    COMMAND ${CMAKE_COMMAND}
    -D gtm_dist=${GTM_BINARY_DIR}
    -D mumps=$<TARGET_FILE:mumps>
    -D input=${GTM_SOURCE_DIR}/${msg}
    -P ${GTM_SOURCE_DIR}/sr_port/msg.cmake
    )
  list(APPEND gen_bootstrap_files gen/${name}_ctl.c)
endforeach()

add_custom_target(gen_bootstrap ALL DEPENDS ${gen_bootstrap_files})
