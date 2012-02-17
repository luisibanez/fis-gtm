#!/usr/bin/tcsh

setenv gtm_curpro $PWD/fake-binary-surrogates
setenv gtm_exe $gtm_curpro
setenv HOSTOS `uname -s`
setenv gtm_tools $PWD/sr_linux
setenv gtm_inc   $PWD/sr_linux
setenv distro ubuntu
setenv gtm_icu_version 4.4
setenv gtm_version_change 1
source sr_unix/gtm_env.csh

echo "----- Start the build -----"
make -f sr_unix/comlist.mk -I./sr_unix -I./sr_linux buildtypes=pro gtm_ver=$PWD  $*
echo "------ End of build -------"

