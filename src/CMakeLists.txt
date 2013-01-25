cmake_minimum_required (VERSION 2.6)
project (3DScanner)

message(${PROJECT_SOURCE_DIR})

# Locate packages
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})



# The version number.
set (Scanner_VERSION_MAJOR 0)
set (Scanner_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/3DScannerConfig.h.in"
  "${PROJECT_BINARY_DIR}/3DScannerConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
# add the executable
add_executable(scan_to_model ${PROJECT_SOURCE_DIR}/utils/scan_to_model/scan_to_model.cpp)
target_link_libraries (scan_to_model ${PCL_LIBRARIES})