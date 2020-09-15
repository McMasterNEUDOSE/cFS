cmake_minimum_required(VERSION 2.6.4)
project(CSP_APP C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(fsw/src)

#required for csp library
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/include)
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/build/include)

#required for subscription table
include_directories(${MISSION_SOURCE_DIR}/apps/comms/fsw/platform_inc)
include_directories(${MISSION_SOURCE_DIR}/apps/eps/fsw/platform_inc)
include_directories(${MISSION_SOURCE_DIR}/apps/payload/fsw/platform_inc)

# Create the app module
add_cfe_app(csp_app fsw/src/csp_app.c)

# Add the subscription table
add_cfe_tables(csp_app fsw/tables/csp_app_subtbl.c)