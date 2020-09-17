cmake_minimum_required(VERSION 2.6.4)
project(CSP_APP C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)

#required for csp library
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/include)
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/build/include)

# Create the app module
add_cfe_app(csp_app fsw/src/csp_app.c)
