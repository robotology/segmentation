# Author : Elena Ceseracciu (RBCS - IIT, 2012)
cmake_minimum_required(VERSION 3.5)

add_subdirectory(edisonlib)

project(EdisonSegmentation)

find_package(ICUBcontrib REQUIRED)
find_package(YARP 3.5.1 REQUIRED COMPONENTS os sig cv)
find_package(OpenCV REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

set(generated_libs_dir "${CMAKE_CURRENT_SOURCE_DIR}")
yarp_idl_to_dir(INPUT_FILES EDISONsegmentation.thrift OUTPUT_DIR ${generated_libs_dir})

include(ICUBcontribOptions)
include(ICUBcontribHelpers)
icubcontrib_set_default_prefix()

include(EDISONsegmentation_thrift.cmake)
source_group("Thrift Source Files" FILES ${sources})
source_group("Thrift Header Files" FILES ${headers})

set(module_source EdisonSegmModule.cpp main.cpp)
set(module_header EdisonSegmModule.h)

source_group("Source Files" FILES ${module_source})
source_group("Header Files" FILES ${module_header})

include_directories(${edisonlib_INCLUDE_DIR}
                    ${generated_libs_dir}/include)

add_executable(${PROJECT_NAME} ${module_source} ${module_header} ${sources} ${headers})
target_link_libraries(${PROJECT_NAME} edisonlib ${YARP_LIBRARIES} ${OpenCV_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_subdirectory(app)


