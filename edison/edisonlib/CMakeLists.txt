#Edison segmentation - lib

project(edisonlib)

#set(edison_source_prompt edison_source/prompt/parser.cpp edison_source/prompt/globalFnc.cpp edison_source/prompt/edison.cpp edison_source/prompt/libppm.cpp)
#set(edison_header_prompt edison_source/prompt/parser.h edison_source/prompt/defs.h edison_source/prompt/error.h edison_source/prompt/flags.h edison_source/prompt/edison.h edison_source/prompt/libppm.h edison_source/prompt/imfilt.h)
set(edison_source_segm src/segm/ms.cpp src/segm/msSysPrompt.cpp src/segm/msImageProcessor.cpp src/segm/RAList.cpp src/segm/rlist.cpp)
set(edison_header_segm include/segm/tdef.h include/segm/RAList.h include/segm/ms.h include/segm/msImageProcessor.h include/segm/msSys.h include/segm/rlist.h)
set(edison_source_edge src/edge/BgEdge.cpp src/edge/BgEdgeDetect.cpp src/edge/BgEdgeList.cpp src/edge/BgGlobalFc.cpp src/edge/BgImage.cpp)
set(edison_header_edge include/edge/BgDefaults.h include/edge/BgEdge.h include/edge/BgEdgeDetect.h include/edge/BgImage.h)
set(folder_source ${edison_source_edge} ${edison_source_segm})
set(folder_header ${edison_header_edge} ${edison_header_segm})

source_group("Source Files" FILES ${folder_source})
source_group("Header Files" FILES ${folder_header})

set(edisonlib_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")

include_directories(${edisonlib_INCLUDE_DIR})
add_library(${PROJECT_NAME} ${folder_source} ${folder_header})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})

