#!/usr/bin/tcsh


#
#  Required Packages
#
#  apt-get install tcsh
#  apt-get install libicu-dev
#  apt-get install gnupg-doc
#  apt-get install zlib1g-dev
#  apt-get install libncurses-dev
#  apt-get install libgcrypt11-dev
#
#


# Path (only directory) to the gtm executables
setenv gtm_curpro /usr/lib/fis-gtm/V5.4-002B_x86
setenv gtm_exe $gtm_curpro
setenv HOSTOS `uname -s`

setenv gtm_tools $PWD/sr_linux
setenv gtm_inc   $PWD/sr_linux

# Tried setting distro to "debian" but got
# error listed in the README file, so used
# distro ubuntu anyways.
setenv distro ubuntu

# NOT set this 32 bits option and let it do a 64 bits build.
# setenv OBJECT_MODE 32

# icu-config --version
# and use only the first two digits
setenv gtm_icu_version 4.4

setenv gtm_version_change 1

source sr_unix/gtm_env.csh



echo "----- Start the build -----"
make -f sr_unix/comlist.mk -I./sr_unix -I./sr_linux buildtypes=pro gtm_ver=$PWD
echo "------ End of build -------"

