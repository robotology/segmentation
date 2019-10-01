/*
 * Copyright (C) 2015 iCub Facility - Istituto Italiano di Tecnologia
 * Authors: Tanis Mar, Giulia Pasquale
 * email:  tanis.mar@iit.it, giulia.pasquale@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

#ifndef __DISPBLOBBERMODULE_H__
#define __DISPBLOBBERMODULE_H__

#include <yarp/os/BufferedPort.h>
#include <yarp/os/RpcClient.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Time.h>
#include <yarp/os/Stamp.h>

#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>

#include <time.h>
#include <string>
#include <iostream>
#include <mutex>

#include "dispBlobber.hpp"

class DispBlobberPort : public yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelBgr> >
{
private:

    std::string moduleName;

    yarp::os::ResourceFinder *moduleRF;

    std::string imgInPortName;

    std::string blobsOutPortName;
    std::string blobsOutPortRightName;
    std::string points3dOutPortName;

    std::string roiOutPortName;
    std::string roiOutPortRightName;

    std::string cropOutPortName;
    std::string optOutPortName;

    yarp::os::BufferedPort<yarp::os::Bottle>							blobsOutPort;
    yarp::os::BufferedPort<yarp::os::Bottle>							blobsOutPortRight;
    yarp::os::BufferedPort<yarp::os::Bottle>							points3dOutPort;

    yarp::os::BufferedPort<yarp::os::Bottle>							roiOutPort;
    yarp::os::BufferedPort<yarp::os::Bottle>							roiOutPortRight;

    yarp::os::BufferedPort< yarp::sig::ImageOf<yarp::sig::PixelBgr> >   cropOutPort;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelMono> >	optOutPort;

    yarp::os::RpcClient 												sfmRpcPort;

    std::vector<cv::Mat> imagesMatBuffer;
    
    dispBlobber *blobExtractor;

    int cropSize;

public:

    DispBlobberPort( const std::string &moduleName, yarp::os::ResourceFinder &module );

    bool        open();
    void        close();
    void        onRead( yarp::sig::ImageOf<yarp::sig::PixelBgr> &img );
    void        interrupt();
    
    bool        setMargin(int mrg);
    bool        setThresh(int low);

    std::mutex  mtx;
       
};

class DispBlobberModule : public yarp::os::RFModule
{

    std::string             moduleName;

    std::string             handlerPortName;    
    yarp::os::RpcServer     handlerPort;

    DispBlobberPort         *blobPort;
    bool                    closing;

public:

    bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
    bool interruptModule();                       // interrupt, e.g., the ports
    bool close();                                 // close and shut down the module

    double getPeriod();
    bool updateModule();
    bool respond(const yarp::os::Bottle &command, yarp::os::Bottle &reply);
};

#endif
//empty line to make gcc happy
