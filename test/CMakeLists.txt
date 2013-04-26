cmake_minimum_required (VERSION 2.6)
project (3DScanner)

set (EXECUTABLE_OUTPUT_PATH ..\bin)

# Locate packages
# PCL
message("Adding PCL...")
find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Boost
message("Adding Boost...")
find_package(Boost 1.46 COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DHAS_BOOST)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("../src")
 
# add test_all executable
add_executable(test_all 
  ${PROJECT_SOURCE_DIR}/test_all.cpp
  ${PROJECT_SOURCE_DIR}/test_preprocessing/test_preprocessing.cpp
  ${PROJECT_SOURCE_DIR}/test_frame/test_frame.cpp
)

# add test_render executable
add_executable(test_rendering
  ${PROJECT_SOURCE_DIR}/test_all.cpp
  ${PROJECT_SOURCE_DIR}/test_render/test_render.cpp
)

target_link_libraries (test_all ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${PCL_LIBRARIES} 3dScanner)
target_link_libraries (test_rendering ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${PCL_LIBRARIES} 3dScanner)