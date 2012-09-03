# Author : Elena Ceseracciu (RBCS - IIT, 2012)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

add_subdirectory(segment) 

SET(PROJECTNAME graphBasedSegmentation)

PROJECT(${PROJECTNAME})

FIND_PACKAGE(YARP)
#FIND_PACKAGE(ICUB)


#thrift file generation -- remember to compile YARP with CREATE_IDLS and ENABLE_yarpidl_thrift options, and to define ALLOW_IDL_GENERATION=ON when configuring this project
INCLUDE(${YARP_MODULE_PATH}/YarpIDL.cmake)
SET(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(graphBasedSegmentationInterface.thrift ${generated_libs_dir})

INCLUDE(graphBasedSegmentationInterface_thrift.cmake)
SOURCE_GROUP("Thrift Source Files" FILES ${sources})
SOURCE_GROUP("Thrift Header Files" FILES ${headers})

    
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
INCLUDE_DIRECTORIES(${YARP_INCLUDE_DIRS}  ${generated_libs_dir}/include ${CMAKE_CURRENT_SOURCE_DIR}/segment)

ADD_EXECUTABLE(${PROJECTNAME} ${module_source} ${module_header} ${sources} ${headers} ${segment_headers})
TARGET_LINK_LIBRARIES(${PROJECTNAME}  ${YARP_LIBRARIES})

install(TARGETS ${PROJECTNAME} DESTINATION bin)

# Adding test client executable - WARNING: it is not added as install target, only built locally!
ADD_EXECUTABLE(testClient testClient.cpp ${sources} ${headers})
TARGET_LINK_LIBRARIES(testClient  ${YARP_LIBRARIES})

