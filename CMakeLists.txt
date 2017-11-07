cmake_minimum_required(VERSION 3.0)
project(dehaze_undewater_image)

######################
## PROJECT SETTINGS ##
######################

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -fpermissive") # -fpermissive
#ADD_DEFINITIONS(-Wno-variadic-macros -Wno-long-long -Wall -Wextra -Winit-self -Woverloaded-virtual -Wsign-promo -Wno-unused-parameter -pedantic -Woverloaded-virtual -Wno-unknown-pragmas -Waddress-of-temporary)

## DEFINE MAIN PATHS
set(bin_path ${PROJECT_BINARY_DIR}/bin)
set(source_path ${PROJECT_SOURCE_DIR}/src)
set(test_path ${PROJECT_SOURCE_DIR}/test)
set(sample_path ${PROJECT_SOURCE_DIR}/sample)

## DEFINE BINARY DESTINE
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_path})

######################
## SOURCE MAIN PATH ##
######################
include_directories(${source_path})
add_subdirectory(${source_path})

###################
##TEST MAIN PATH ##
###################
enable_testing()
add_subdirectory(${test_path})

# ######################
# ## SAMPLE MAIN PATH ##
# ######################
# include_directories(${sample_path})
# add_subdirectory(${sample_path})
