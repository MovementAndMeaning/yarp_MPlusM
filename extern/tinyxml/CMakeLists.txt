# Copyright (C) 2012  iCub Facility, Istituto Italiano di Tecnologia
# Author: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


# TinyXML
project(YARP_priv_tinyxml)

set(tinyxml_SRCS
    tinyxml/tinystr.cpp
    tinyxml/tinyxml.cpp
    tinyxml/tinyxmlerror.cpp
    tinyxml/tinyxmlparser.cpp
)

set(tinyxml_HDRS
    tinyxml/tinystr.h
    tinyxml/tinyxml.h
)

add_definitions("-DTIXML_USE_STL")

add_library(YARP_priv_tinyxml STATIC ${tinyxml_SRCS})

set(TinyXML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml PARENT_SCOPE)
set(TinyXML_LIBRARIES "YARP_priv_tinyxml" PARENT_SCOPE)
set(TinyXML_DEFINITIONS "-DTIXML_USE_STL" PARENT_SCOPE)

if(YARP_EXPERIMENTAL_MANAGER_LIB)
    install(TARGETS YARP_priv_tinyxml
            EXPORT YARP
            COMPONENT runtime
            DESTINATION ${CMAKE_INSTALL_LIBDIR})
    set_property(GLOBAL APPEND PROPERTY YARP_LIBS YARP_priv_tinyxml)
endif()
