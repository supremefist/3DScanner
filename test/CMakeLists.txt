cmake_minimum_required (VERSION 2.6)
project (3DScanner)

message(${PROJECT_SOURCE_DIR})

# Locate packages
# PCL
find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

message("Hello")

# Boost
find_package(Boost 1.46 COMPONENTS unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DHAS_BOOST)
#add_definitions(-DBOOST_TEST_DYN_LINK)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
# add the executable
add_executable(test_all 
  ${PROJECT_SOURCE_DIR}/test_all.cpp
  ${PROJECT_SOURCE_DIR}/test_preprocessing/test_preprocessing.cpp
  ${PROJECT_SOURCE_DIR}/test_frame/test_frame.cpp
)

target_link_libraries (test_all ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
