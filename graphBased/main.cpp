// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/** 
\defgroup icub_graphbasedSegmentation graphbasedSegmentation

Wrapper module that performs graph-based image segmentation exploiting the algorithm developed by Felzenszwalb and Huttenlocher (Brown University).

\section intro_sec Description

Wrapper module that performs graph-based image segmentation exploiting the algorithm developed by Felzenszwalb and Huttenlocher (Brown University). The algorithm is described in the paper "Efficient Graph-Based Image Segmentation", Pedro F. Felzenszwalb and Daniel P. Huttenlocher, International Journal of Computer Vision, Volume 59, Number 2, September 2004. The original code is available from http://www.cs.brown.edu/~pff/segment/ and has been copied into the src/segmentation/graphBased/segment folder.

\section lib_sec Libraries
YARP library.

\section parameters_sec Parameters
- \c name name of the module (for opened ports)
- \c sigma smoothing parameter (standard deviation of a Gaussian filter used to pre-process image, in order to compensate
for digitization artifacts)
- \c k scale factor for boundary-detection threshold function (a larger k causes a preference for larger components).
- \c minRegion minumum size of a component.


\section portsa_sec Ports Accessed
None.

\section portsc_sec Ports Created
- /<module_name>/rawImg:i input port where original images must be sent (default: GBSeg)
- /<module_name>/viewImg:o
- /<module_name>/conf rpc port, accepts the commands defined in \link graphBasedSegmentationInterface.thrift  graphBasedSegmentationInterface.thrift \endlink and documented \link SegmentationModuleInterface here \endlink
    

\section in_files_sec Input Data Files
None

\section out_data_sec Output Data Files
None

\section conf_file_sec Configuration Files
No configuration file is needed. Parameters described in \ref parameters_sec can be provided in a configuration file; default filename is 


\section tested_os_sec Tested OS
Linux and Windows.

\section example_sec Example Instantiation of the Module

Examples of module use are provided in the app/scripts folder, and installed into app/graphBasedSegm/scripts.

\author Elena Ceseracciu


Copyright (C) 2012 RBCS - Istituto Italiano di Tecnologia

CopyPolicy: Released under the terms of the GNU GPL v2.0 and later.


This file can be edited at src/segmentation/graphBased/main.cpp.
*/ 


// yarp
#include <yarp/os/Network.h>
using namespace yarp::os;

#include "SegmModule.h"


int main(int argc, char *argv[])
{
    Network yarp;   
    if (!yarp.checkNetwork())
        return 1;

    ResourceFinder rf;
    rf.setDefaultContext("graphBasedSegm");
    rf.setDefaultConfigFile("config.ini");
    rf.configure(argc,argv);

    GBSegmModule mod;
    return mod.runModule(rf);
}
