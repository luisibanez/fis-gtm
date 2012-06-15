set(ENV{gtm_dist} "${gtm_dist}")
set(ENV{gtmroutines} ".")
execute_process(
  COMMAND ${mumps} -run msg ${input} unix
  )
