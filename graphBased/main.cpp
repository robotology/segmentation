// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/** 
@ingroup icub_module

\defgroup 

\section intro_sec Description

\section lib_sec Libraries
YARP library


\section parameters_sec Parameters


\section portsa_sec Ports Accessed


\section portsc_sec Ports Created

\section in_files_sec Input Data Files
None

\section out_data_sec Output Data Files
None

\section conf_file_sec Configuration Files



\section tested_os_sec Tested OS
Linux and Windows.

\section example_sec Example Instantiation of the Module

\code

\endcode

\author Elena Ceseracciu (improved module version)


Copyright (C) 2012 RBCS - Istituto Italiano di Tecnologia

CopyPolicy: Released under the terms of the GNU GPL v2.0 and later.


This file can be edited at src/segmentation/graphBased/main.cpp.
*/ 


// yarp
#include <yarp/os/Network.h>
#include <yarp/os/Module.h>
using namespace yarp::os;

#include "SegmModule.h"


int main(int argc, char *argv[]) {
   
    Network yarp;   

    if (!yarp.checkNetwork())
        return -1;


    ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultContext("graphBasedSegm/conf");
    rf.setDefaultConfigFile("config.ini");
    rf.configure("ICUB_ROOT",argc,argv);

    GBSegmModule mod;

    return mod.runModule(rf);
    
}
