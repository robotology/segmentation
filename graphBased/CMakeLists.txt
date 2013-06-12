# Author : Elena Ceseracciu (RBCS - IIT, 2012)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

add_subdirectory(segment) 

SET(PROJECTNAME graphBasedSegmentation)

PROJECT(${PROJECTNAME})

FIND_PACKAGE(YARP)

#create Thrift-generated library first 
add_subdirectory (thriftGBseg)
# Source code listing
set(segment_headers segment/convolve.h segment/disjoint-set.h segment/filter.h segment/image.h segment/imconv.h segment/imutil.h segment/misc.h segment/pnmfile.h segment/segment-graph.h segment/segment-image.h)

SOURCE_GROUP("Segmentation Source Files" FILES ${segment_headers})

SET(module_source SegmModule.cpp main.cpp)
SET(module_header SegmModule.h)

SOURCE_GROUP("Source Files" FILES ${module_source})
SOURCE_GROUP("Header Files" FILES ${module_header})

# install sample application
add_subdirectory(app)

# Set up the executable.
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS}  ${thriftGBseg_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/segment)

ADD_EXECUTABLE(${PROJECTNAME} ${module_source} ${module_header} ${segment_headers})
TARGET_LINK_LIBRARIES(${PROJECTNAME} thriftGBseg ${YARP_LIBRARIES})

install(TARGETS ${PROJECTNAME} DESTINATION ${ICUB_DIR}/bin)

# Adding test client executable - WARNING: it is not added as install target, only built locally!
ADD_EXECUTABLE(testClient testClient.cpp)
TARGET_LINK_LIBRARIES(testClient thriftGBseg ${YARP_LIBRARIES})

