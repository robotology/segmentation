# Copyright: 2015 iCub Facility, Istituto Italiano di Tecnologia
# Authors: Tanis Mar, Giulia Pasquale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# 

cmake_minimum_required(VERSION 2.6)
project(dispBlobber)

find_package(YARP REQUIRED)
find_package(ICUBcontrib REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

find_package(OpenCV)

include(YarpInstallationHelpers)
include(ICUBcontribHelpers)
include(ICUBcontribOptions)
icubcontrib_set_default_prefix()

add_definitions(${YARP_DEFINES})

file(GLOB source src/*.cpp)
file(GLOB header inc/*.h)

source_group("Source Files" FILES ${source})
source_group("Header Files" FILES ${header})
source_group("DOC Files"    FILES ${PROJECT_NAME}.xml)

include_directories(${PROJECT_SOURCE_DIR}/inc
                    ${YARP_INCLUDE_DIRS}
                    ${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${source} ${header} ${PROJECT_NAME}.xml)
target_link_libraries(${PROJECT_NAME} ${YARP_LIBRARIES} ${OpenCV_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
yarp_install(FILES ${PROJECT_NAME}.xml DESTINATION ${ICUBCONTRIB_MODULES_INSTALL_DIR})

file(GLOB conf      ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/*.ini)
file(GLOB templates ${CMAKE_CURRENT_SOURCE_DIR}/app/scripts/*.xml.template)

yarp_install(FILES ${conf}      DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${PROJECT_NAME})
yarp_install(FILES ${templates} DESTINATION ${ICUBCONTRIB_APPLICATIONS_TEMPLATES_INSTALL_DIR})

