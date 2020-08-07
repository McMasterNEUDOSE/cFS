#!/bin/bash
section="############################################################"

printf '\n%s\nBUILDING CSP LIBRARY...\n%s\n\n' $section $section;
cd apps/libcsp;
./waf configure --install-csp --with-driver-usart=linux --out=build/cpu1/apps/csp;
./waf build;
cd ../..;

printf '\n%s\nCSP BUILD FINISHED\nRUNNING MAKE PREP...\n%s\n\n' $section $section;
make prep;

printf '\n%s\nMAKE PREP FINISHED\nRUNNING MAKE...\n%s\n\n' $section $section;
make;

printf '\n%s\nMAKE FINISHED\nRUNNING MAKE INSTALL...\n%s\n\n' $section $section;

make install;
printf '\n%s\nMAKE INSTALL FINISHED\nRUNNING CFS...\n%s\n\n' $section $section;
cd build/exe/cpu1 && sudo ./core-cpu1
