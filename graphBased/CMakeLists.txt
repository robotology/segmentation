# Author : Elena Ceseracciu (RBCS - IIT, 2012)
cmake_minimum_required(VERSION 3.5)

#add_subdirectory(segment) 

project(graphBasedSegmentation)

find_package(ICUBcontrib REQUIRED)
find_package(YARP REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

include(ICUBcontribHelpers)
include(ICUBcontribOptions)
icubcontrib_set_default_prefix()
#create Thrift-generated library first 
add_subdirectory (thriftGBseg)
# Source code listing
set(segment_headers segment/convolve.h segment/disjoint-set.h segment/filter.h segment/image.h segment/imconv.h segment/imutil.h segment/misc.h segment/pnmfile.h segment/segment-graph.h segment/segment-image.h)

source_group("Segmentation Source Files" FILES ${segment_headers})

set(module_source SegmModule.cpp main.cpp)
set(module_header SegmModule.h)

source_group("Source Files" FILES ${module_source})
source_group("Header Files" FILES ${module_header})

# install sample application
add_subdirectory(app)

# Set up the executable.
include_directories(${thriftGBseg_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/segment)

add_executable(${PROJECT_NAME} ${module_source} ${module_header} ${segment_headers})
target_link_libraries(${PROJECT_NAME} thriftGBseg ${YARP_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Adding test client executable - WARNING: it is not added as install target, only built locally!
add_executable(testGbsClient testGbsClient.cpp)
target_link_libraries(testGbsClient thriftGBseg ${YARP_LIBRARIES})

