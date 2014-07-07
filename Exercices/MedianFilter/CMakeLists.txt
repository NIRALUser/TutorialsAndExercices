# This is the root ITK CMakeList file: 
cmake_minimum_required(VERSION 2.8)

# This project is designed to be built outside the Insight source tree.
project(MedianFilter)

# Find Slicer3
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

# Find GenerateCLP
find_package(GenerateCLP REQUIRED)
include(${GenerateCLP_USE_FILE})
 
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

set(MedianFilter_SOURCE MedianFilter.cxx)
GENERATECLP(MedianFilter_SOURCE MedianFilter.xml) 

add_executable(MedianFilter ${MedianFilter_SOURCE})

target_link_libraries(MedianFilter ${ITK_LIBRARIES})

