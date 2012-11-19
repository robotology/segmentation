# Author: Elena Ceseracciu, RBCS - Istituto Italiano di Tecnologia
find_package(ICUB)
set(CMAKE_MODULE_PATH ${ICUB_MODULE_PATH} ${CMAKE_MODULE_PATH})
include(iCubHelpers)

set(appname graphBasedSegm)
icub_app(${appname})

file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini)
file(GLOB scripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*.template)

set(ICUB_APPLICATIONS_PREFIX "$ENV{ICUB_ROOT}" CACHE PATH "Application path prefix")

icub_app_install(${appname} 
                 FILES ${conf}
                 DESTINATION conf/)

icub_app_install(${appname} 
                FILES ${scripts}
                DESTINATION scripts/)

### create a single target that installs all applications at once
icub_app_all()

