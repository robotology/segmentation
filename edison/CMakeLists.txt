# Author : Elena Ceseracciu (RBCS - IIT, 2012)
cmake_minimum_required(VERSION 2.6)

add_subdirectory(edisonlib)

project(EdisonSegmentation)

find_package(YARP REQUIRED)
find_package(ICUBcontrib REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH}
                              ${ICUBCONTRIB_MODULE_PATH})
find_package(OpenCV REQUIRED)

include(YarpInstallationHelpers)
include(YarpIDL)
set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(${PROJECT_NAME}.thrift ${generated_libs_dir})

include(ICUBcontribHelpers)
icubcontrib_set_default_prefix()

include(${PROJECT_NAME}_thrift.cmake)
source_group("Thrift Source Files" FILES ${sources})
source_group("Thrift Header Files" FILES ${headers})

set(module_source EdisonSegmModule.cpp main.cpp)
set(module_header EdisonSegmModule.h)

source_group("Source Files" FILES ${module_source})
source_group("Header Files" FILES ${module_header})

include_directories(${edisonlib_INCLUDE_DIR}
                    ${YARP_INCLUDE_DIRS}
                    ${OpenCV_INCLUDE_DIRS}
                    ${generated_libs_dir}/include)

add_executable(${PROJECT_NAME} ${module_source} ${module_header} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} edisonlib ${YARP_LIBRARIES} ${OpenCV_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_subdirectory(app)


