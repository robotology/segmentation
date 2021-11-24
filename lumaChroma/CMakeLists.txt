# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Vadim Tikhanoff
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(lumaChroma)

find_package(ICUBcontrib REQUIRED)
find_package(YARP 3.5.1 REQUIRED COMPONENTS os sig cv)
find_package(OpenCV REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

include(ICUBcontribHelpers)
include(ICUBcontribOptions)
icubcontrib_set_default_prefix()

# Search for source code.
set(doc_files ${PROJECT_NAME}.xml)
source_group("DOC Files" FILES ${doc_files})

file(GLOB folder_source src/*.cpp src/*.cc src/*.c)
file(GLOB folder_header include/*.h)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${folder_header} ${folder_source})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES} ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

yarp_install(FILES ${doc_files} DESTINATION ${ICUBCONTRIB_MODULES_INSTALL_DIR})
add_subdirectory(app)
