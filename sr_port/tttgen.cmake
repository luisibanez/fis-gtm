set(ENV{gtm_dist} "${gtm_dist}")
set(ENV{gtmroutines} ".")
execute_process(
  COMMAND ${mumps} -run tttgen ${input} ${sr_port}/opcode_def.h ${sr_port}/vxi.h
  OUTPUT_FILE ttt.log
  )
