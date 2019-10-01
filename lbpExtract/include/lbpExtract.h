/*
 * Copyright (C) 2015 Department of iCub Facility - Istituto Italiano di Tecnologia
 * Author: Vadim Tikhanoff
 * email:  vadim.tikhanoff@iit.it
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

#ifndef __ICUB_LBPEXTRACT_MOD_H__
#define __ICUB_LBPEXTRACT_MOD_H__

#include <yarp/os/BufferedPort.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/PeriodicThread.h>
#include <yarp/os/Time.h>
#include <yarp/os/Stamp.h>
#include <yarp/os/RpcClient.h>
#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>

#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <mutex>

#include <cstdio>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#include "lbp.h"
#include "histogram.h"

#include <lbpExtract_IDLServer.h>


class SEGMENTManager : public yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >
{
private:
    
    std::string moduleName;                 //string containing module name
    std::string inPortName;                 //string containing image input port name

    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >        outPortPropagate;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >        outPortBlobs;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >        outPortSegmented;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelMono> >       outPortLbp;
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelMono> >       outPortLbpContours;
    
    yarp::os::BufferedPort<yarp::os::Bottle>                                outTargetPort;

    cv::Mat imgMat;
    int     radius, defaultRadius;
    int     neighbours, defaultNeighbours;
    int     topBound, defaultTopBound;
    int     minArcLength, defaultMinArcLength;
    int     maxArcLength, defaultMaxArcLength;
    int     numIteration, defaultNumIteration;
    int     minArea, defaultMinArea;
    int     maxArea, defaultMaxArea;
    int     minWidth, defaultMinWidth;
    int     bbOffset;
    bool    verbose;
    
    cv::Mat segmented;
    yarp::os::Bottle allPoints;
    yarp::os::Bottle& getComponents(cv::Mat &img, int x, int y);
    std::mutex semComp;
    
public:
    
    /**
     * constructor
     * @param moduleName is passed to the thread in order to initialise all the ports correctly (default yuvProc)
     * @param imgType is passed to the thread in order to work on YUV or on HSV images (default yuv)
     */
    SEGMENTManager( const std::string &moduleName );
    ~SEGMENTManager();
    
    std::mutex mtx;

    bool    open();
    void    close();
    void    onRead( yarp::sig::ImageOf<yarp::sig::PixelRgb> &img );
    void    interrupt();
    
    bool setDefaultValues(const int32_t radius, const int32_t neighbours, const int32_t topBound, const int32_t minArcLength, const int32_t maxArcLength, const int32_t numIteration, const int32_t minArea, const int32_t maxArea, const int32_t minWidth );
    
    bool setRadius(const int32_t radius);
    bool setNeighbours(const int32_t neighbours);
    bool setTopBound(const int32_t topBound);
    bool setMinArcLength(const int32_t minArcLength);
    bool setMaxArcLength(const int32_t maxArcLength);
    bool setNumIteration(const int32_t numIteration);
    bool setMinArea(const int32_t minArea);
    bool setMaxArea(const int32_t maxArea);
    bool setMinWidth(const int32_t minWidth);
    bool setbbOffset(const int32_t offset);
    bool resetAllValues();
    bool verbosity(const int32_t boolVerbosity);
    
    int32_t getRadius();
    int32_t getNeighbours();
    int32_t getTopBound();
    int32_t getMinArcLength();
    int32_t getMaxArcLength();
    int32_t getMinArea();
    int32_t getMaxArea();
    int32_t getMinWidth();
    int32_t getNumIteration();
    int32_t getbbOffset();
    yarp::os::Bottle get_component_around(const int32_t x, const int32_t y);
};

class SEGMENTModule:public yarp::os::RFModule, public lbpExtract_IDLServer
{
    /* module parameters */
    std::string             moduleName;
    std::string             handlerPortName;
    yarp::os::RpcServer     rpcPort;

    /* pointer to a new thread */
    SEGMENTManager          *segmentManager;
    bool                    closing;
    
    friend class segmentManager;
public:
    

    bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
    bool interruptModule();                       // interrupt, e.g., the ports
    bool close();                                 // close and shut down the module

    bool attach(yarp::os::RpcServer &source);
    bool reset();
    bool quit();
    
    bool setRadius(const int32_t radius);
    bool setNeighbours(const int32_t neighbours);
    bool setTopBound(const int32_t topBound);
    bool setMinArcLength(const int32_t minArcLength);
    bool setMaxArcLength(const int32_t maxArcLength);
    bool setNumIteration(const int32_t numIteration);
    bool setMinArea(const int32_t minArea);
    bool setMaxArea(const int32_t maxArea);
    bool setMinWidth(const int32_t minWidth);
    bool resetAllValues();
    bool verbosity(const int32_t boolVerbosity);
    bool setbbOffset(const int32_t offset);
    
    int32_t getRadius();
    int32_t getNeighbours();
    int32_t getTopBound();
    int32_t getMinArcLength();
    int32_t getMaxArcLength();
    int32_t getMinArea();
    int32_t getMaxArea();
    int32_t getMinWidth();
    int32_t getNumIteration();
    int32_t getbbOffset();
    yarp::os::Bottle get_component_around(const int32_t x, const int32_t y);

    double getPeriod();
    bool updateModule();
};


#endif
//empty line to make gcc happy
