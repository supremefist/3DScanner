cmake_minimum_required (VERSION 2.6)
project (3DScanner)

set (EXECUTABLE_OUTPUT_PATH ../bin)

message(${PROJECT_SOURCE_DIR})

# Locate packages
find_package(PCL 1.6 REQUIRED)
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

# add frame_viewer library
add_library(3dScanner 
	utils/frame_viewer/frame_viewer.cpp
	utils/frame_viewer/frame_viewer.h
	components/frame/frame.cpp
	components/frame/frame.h
)
target_link_libraries (3dScanner ${PCL_LIBRARIES})

# add the executables
add_executable(scan_to_model ${PROJECT_SOURCE_DIR}/utils/scan_to_model/scan_to_model.cpp)
target_link_libraries (scan_to_model 3dScanner)

add_executable(register_clouds ${PROJECT_SOURCE_DIR}/utils/register_clouds/register_clouds.cpp)
target_link_libraries (register_clouds 3dScanner)

add_executable(registration_demo ${PROJECT_SOURCE_DIR}/utils/registration_demo/registration_demo.cpp)
target_link_libraries (registration_demo 3dScanner)

add_executable(frame_viewer ${PROJECT_SOURCE_DIR}/utils/frame_viewer/frame_viewer.cpp)
target_link_libraries (frame_viewer 3dScanner)
