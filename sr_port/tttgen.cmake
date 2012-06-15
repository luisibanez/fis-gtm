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
execute_process(
  COMMAND ${mumps} -run tttgen ${input} ${sr_port}/opcode_def.h ${sr_port}/vxi.h
  OUTPUT_FILE ttt.log
  )
