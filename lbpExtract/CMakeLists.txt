# Copyright: 2012 iCub Facility, Istituto Italiano di Tecnologia
# Author: Vadim Tikhanoff
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 2.8.9)
project(lbpExtract)

find_package(YARP)
find_package(ICUB)
find_package(ICUBcontrib)

list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

find_package(OpenCV)

include(YarpInstallationHelpers)
include(ICUBcontribHelpers)
include(ICUBcontribOptions)
icubcontrib_set_default_prefix()

include(YarpIDL)
yarp_add_idl(IDL_GEN_FILES ${PROJECT_NAME}.thrift)

file(GLOB source src/*.cpp)
file(GLOB header include/*.h)
set(idl ${PROJECT_NAME}.thrift)
set(doc ${PROJECT_NAME}.xml)

source_group("Source Files" FILES ${source})
source_group("Header Files" FILES ${header})
source_group("IDL Files" FILES ${idl})
source_group("DOC Files" FILES ${doc})

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${OpenCV_INCLUDE_DIRS}
                    ${YARP_INCLUDE_DIRS}
                    ${ICUB_INCLUDE_DIRS})

add_definitions(-D_USE_MATH_DEFINES)
add_executable(${PROJECT_NAME} ${source} ${header} ${doc} ${idl} ${IDL_GEN_FILES})
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES} ${OpenCV_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
yarp_install(FILES ${doc} DESTINATION ${ICUBCONTRIB_MODULES_INSTALL_DIR})

add_subdirectory(app)
