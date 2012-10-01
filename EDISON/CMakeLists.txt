# Author : Elena Ceseracciu (RBCS - IIT, 2012)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

add_subdirectory(edisonlib) 

SET(PROJECTNAME EdisonSegmentation)

PROJECT(${PROJECTNAME})

FIND_PACKAGE(YARP)
#FIND_PACKAGE(ICUB)
FIND_PACKAGE(OpenCV)

#thrift file generation -- remember to compile YARP with CREATE_IDLS and ENABLE_yarpidl_thrift options, and to define ALLOW_IDL_GENERATION=ON when configuring this project
INCLUDE(${YARP_MODULE_PATH}/YarpIDL.cmake)
SET(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(EDISONsegmentation.thrift ${generated_libs_dir})

INCLUDE(EDISONsegmentation_thrift.cmake)
SOURCE_GROUP("Thrift Source Files" FILES ${sources})
SOURCE_GROUP("Thrift Header Files" FILES ${headers})

    
# Source code listing
SET(module_source EdisonSegmModule.cpp main.cpp)
SET(module_header EdisonSegmModule.h)

SOURCE_GROUP("Source Files" FILES ${module_source})
SOURCE_GROUP("Header Files" FILES ${module_header})


# Set up the executable.
INCLUDE_DIRECTORIES(${edisonlib_INCLUDE_DIR} ${YARP_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${generated_libs_dir}/include )

ADD_EXECUTABLE(${PROJECTNAME} ${module_source} ${module_header} ${sources} ${headers})
TARGET_LINK_LIBRARIES(${PROJECTNAME}  edisonlib ${YARP_LIBRARIES} ${OpenCV_LIBRARIES})

install(TARGETS ${PROJECTNAME} DESTINATION bin)

# install sample application
add_subdirectory(app)
