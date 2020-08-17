#!/bin/bash
section="############################################################"

printf '\n%s\nBUILDING CSP LIBRARY...\n%s\n\n' $section $section;
cd apps/libcsp;
./waf configure --install-csp --with-driver-usart=linux --enable-shlib;
./waf build;
cd ../..;

printf '\n%s\nCSP BUILD FINISHED\nRUNNING MAKE PREP...\n%s\n\n' $section $section;
make prep;

printf '\n%s\nMAKE PREP FINISHED\nRUNNING MAKE...\n%s\n\n' $section $section;
make;

printf '\n%s\nMAKE FINISHED\nRUNNING MAKE INSTALL...\n%s\n\n' $section $section;
make install;

printf '\n%s\nMAKE INSTALL FINISHED\nINSTALLING CSP...\n%s\n\n' $section $section;
cp apps/libcsp/build/libcsp.so build/exe/cpu1/cf/libcsp.so;
chmod -x build/exe/cpu1/cf/libcsp.so;

printf '\n%s\nCSP INSTALL FINISHED\nSTARTING CFS...\n%s\n\n' $section $section;
cd build/exe/cpu1 && sudo ./core-cpu1
