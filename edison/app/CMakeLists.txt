# Author: Elena Ceseracciu, RBCS - Istituto Italiano di Tecnologia

file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/conf/*.ini)
file(GLOB scripts ${CMAKE_CURRENT_SOURCE_DIR}/scripts/*.template)

yarp_install(FILES ${conf}    DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/edisonSegm)
yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_APPLICATIONS_TEMPLATES_INSTALL_DIR})


