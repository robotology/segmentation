# Copyright: (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
# Authors: Carlo Ciliberto
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(blobExtractor)

find_package(YARP REQUIRED)
find_package(ICUB REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})

find_package(OpenCV REQUIRED)

find_package(ICUBcontrib REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})
include(ICUBcontribHelpers)
include(ICUBcontribOptions)
icubcontrib_set_default_prefix()

include_directories(${OpenCV_INCLUDE_DIRS})

set(folder_source main.cpp)
source_group("Source Files" FILES ${folder_source})

add_definitions(-D_USE_MATH_DEFINES)
add_executable(${PROJECT_NAME} ${folder_source})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES} ${YARP_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_subdirectory(app)

