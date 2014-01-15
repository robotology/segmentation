# Author : Elena Ceseracciu (IIT, 2012)
project(thriftGBseg)

#thrift file generation -- remember to compile YARP with CREATE_IDLS and ENABLE_yarpidl_thrift options, and to define ALLOW_IDL_GENERATION=ON when configuring this project
include(YarpIDL)
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(iCub/segmentation/graphBasedSegmentationInterface.thrift ${generated_libs_dir})

set(THRIFT_HEADERS)
set(THRIFT_SOURCES)

set(fileList iCub_segmentation_graphBasedSegmentationInterface_thrift.cmake)
foreach(scriptFile ${fileList})
  include(${scriptFile})
  list(APPEND THRIFT_HEADERS ${headers})
  list(APPEND THRIFT_SOURCES ${sources})
endforeach()
#message ("Thrift headers ${THRIFT_HEADERS}.\n Thirft sources: ${THRIFT_SOURCES}")

source_group("Thrift Source Files" FILES ${sources})
source_group("Thrift Header Files" FILES ${headers})
include_directories(include ${YARP_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${THRIFT_HEADERS} ${THRIFT_SOURCES})
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

icubcontrib_export_library(${PROJECT_NAME} INTERNAL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
                                   EXTERNAL_INCLUDE_DIRS ${YARP_INCLUDE_DIRS}
                                   DESTINATION include/iCub/segmentation
                                   FILES ${THRIFT_HEADERS})

icubcontrib_finalize_export(thriftGBseg)