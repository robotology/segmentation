set(PROJECTNAME thriftGBseg)
project(${PROJECTNAME})

#thrift file generation -- remember to compile YARP with CREATE_IDLS and ENABLE_yarpidl_thrift options, and to define ALLOW_IDL_GENERATION=ON when configuring this project
INCLUDE(${YARP_MODULE_PATH}/YarpIDL.cmake)
SET(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
#yarp_idl_to_dir(graphBasedSegmentationInterface.thrift ${generated_libs_dir})


set(THRIFT_HEADERS)
set(THRIFT_SOURCES)

set(fileList graphBasedSegmentationInterface_thrift.cmake)
foreach(scriptFile ${fileList})
  include(${scriptFile})
  list(APPEND THRIFT_HEADERS ${headers})
  list(APPEND THRIFT_SOURCES ${sources})
endforeach()
#message ("Thrift headers ${THRIFT_HEADERS}.\n Thirft sources: ${THRIFT_SOURCES}")

SOURCE_GROUP("Thrift Source Files" FILES ${sources})
SOURCE_GROUP("Thrift Header Files" FILES ${headers})
include_directories(include ${YARP_INCLUDE_DIRS})

add_library(${PROJECTNAME} ${THRIFT_HEADERS} ${THRIFT_SOURCES})
target_link_libraries(${PROJECTNAME} ${YARP_LIBRARIES})
set_target_properties(${PROJECTNAME} PROPERTIES LINKER_LANGUAGE CXX)

export(TARGETS ${PROJECTNAME} FILE ${CMAKE_BINARY_DIR}/${PROJECTNAME}.cmake)

install(TARGETS ${PROJECTNAME} EXPORT ${PROJECTNAME} DESTINATION ${ICUB_DIR}/lib)
install(EXPORT ${PROJECTNAME} DESTINATION ${ICUB_DIR}/lib/${PROJECTNAME})

export(PACKAGE ${PROJECTNAME})
get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
configure_file(libraryConfig.cmake.in ${CMAKE_BINARY_DIR}/${PROJECTNAME}Config.cmake @ONLY)
get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
set(${PROJECTNAME}_INCLUDE_DIRS ${inc_dirs} CACHE INTERNAL "Generated-files libraries include directory")
