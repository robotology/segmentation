
cmake_minimum_required(VERSION 3.5)

project(segmentation)

find_package(ICUBcontrib REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})
include(ICUBcontribOptions)
include(ICUBcontribHelpers)

add_subdirectory(edison)
add_subdirectory(graphBased)
add_subdirectory(lumaChroma)
add_subdirectory(blobExtractor)
add_subdirectory(lbpExtract)
add_subdirectory(dispBlobber)
add_subdirectory(seg2cloud)

icubcontrib_add_uninstall_target()
