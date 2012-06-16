#################################################################
#								#
#	Copyright 2012 Fidelity Information Services, Inc	#
#								#
#	This source code contains the intellectual property	#
#	of its copyright holder(s), and is made available	#
#	under a license.  If you do not know the terms of	#
#	the license, please stop and do not read further.	#
#								#
#################################################################
set(ENV{gtm_dist} "${gtm_dist}")
set(ENV{gtmroutines} ".")
set(ENV{gtm_chset} "${gtm_chset}")
set(ENV{gtm_icu_version} "${gtm_icu_version}")
if(output_file)
  set(output_file OUTPUT_FILE ${output_file})
endif()
execute_process(
  COMMAND ${mumps} ${args}
  ${output_file}
  )
