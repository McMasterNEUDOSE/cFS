cmake_minimum_required(VERSION 2.6.4)
project(CSP_APP C)

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(fsw/src)
include_directories(test_and_ground)

#required for csp library
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/include)
include_directories(${MISSION_SOURCE_DIR}/apps/libcsp/build/include)

#required for subscription table
include_directories(${MISSION_SOURCE_DIR}/apps/comms/fsw/platform_inc)
include_directories(${MISSION_SOURCE_DIR}/apps/eps/fsw/platform_inc)
include_directories(${MISSION_SOURCE_DIR}/apps/payload/fsw/platform_inc)

aux_source_directory(fsw/src APP_SRC_FILES)
aux_source_directory(test_and_ground APP_SRC_FILES)

# Create the app module
add_cfe_app(csp_app ${APP_SRC_FILES})

# Add the subscription table
add_cfe_tables(csp_app fsw/tables/csp_app_subtbl.c)