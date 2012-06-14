set(ENV{gtm_dist} "${gtm_dist}")
execute_process(
  COMMAND ${mumps} -run msg ${input} unix
  )
