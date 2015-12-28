
cmake_minimum_required(VERSION 2.6)

project(segmentation)

find_package(ICUBcontrib REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})
include(ICUBcontribHelpers)

add_subdirectory(edison)
add_subdirectory(graphBased)

icubcontrib_add_uninstall_target()

