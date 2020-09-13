cmake_minimum_required(VERSION 2.6.4)
project(CSP_APP C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)

#required for csp library
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/include)
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/build/include)

include_directories(${to_lab_MISSION_DIR}/fsw/src)
include_directories(${to_lab_MISSION_DIR}/fsw/mission_inc)
include_directories(${to_lab_MISSION_DIR}/fsw/platform_inc)
include_directories(${ci_lab_MISSION_DIR}/fsw/platform_inc)
include_directories(${sample_app_MISSION_DIR}/fsw/platform_inc)
include_directories(${eps_MISSION_DIR}/fsw/platform_inc)
include_directories(${comms_MISSION_DIR}/fsw/platform_inc)
include_directories(${payload_MISSION_DIR}/fsw/platform_inc)

# Create the app module
add_cfe_app(csp_app fsw/src/csp_app.c)
