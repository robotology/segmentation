/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
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

#ifndef __ICUB_BLOBSPOTTER_MOD_H__
#define __ICUB_BLOBSPOTTER_MOD_H__

#include <yarp/os/BufferedPort.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Time.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Stamp.h>
#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>

#include <yarp/os/RpcClient.h>

#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>

#include <opencv2/opencv.hpp>

#include "utils.h"

#include "histogram.h"
#include "colorhistogram.h"
#include "objectFinder.h"

#include <blobSpotter_IDLServer.h>
#include <map>

#define MAX_HISTS 10

struct histDetails
{
    //variables needed by histogram
    cv::Rect                rect;
    ObjectFinder            finder;
    ColorHistogram          hc;
    cv::SparseMat           shist;
};

class SPOTTERManager : public yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >
{
private:

    std::string moduleName;              //string containing module name
    std::string inImgPortName;           //string containing image input port name
    std::string inRoiPortName;           //string containing template input port name

    std::string outImgOrigPortName;      //string containing image output port name
    std::string outImgPortName;          //string containing image output port name
    std::string outTargetPortName;       //string containing target output port name

    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >    imageOrigPort;         //output port Image
    yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> >    imageOutPort;          //output port Image
    yarp::os::BufferedPort<yarp::os::Bottle>                            targetOutPort;          //output port containing targets

    ROIPoints     roiPoints;      //class to receive points from fixation point
    friend class  ROIPoints;
    histDetails  *histParams;

    cv::Mat       imgMat;
    cv::Mat       imageROI;
    cv::Mat       result;
    cv::Mat       histogram;
    int           time;

public:
    /**
     * constructor
     * @param moduleName is passed to the thread in order to initialise all the ports correctly (default yuvProc)
     * @param imgType is passed to the thread in order to work on YUV or on HSV images (default yuv)
     */
    SPOTTERManager( const std::string &moduleName );
    ~SPOTTERManager();

    bool                        deleted;
    bool                        isInitialised;
    int                         histCnt;
    int                         histIndex;
    std::vector<cv::Point2f>    roi;
    yarp::os::Semaphore         mutex;
    int                         minArea;
    int                         maxArea;
    int                         topBound;

    bool    open();
    void    close();
    void    onRead( yarp::sig::ImageOf<yarp::sig::PixelRgb> &img );
    void    interrupt();
    void    processRoiPoints(yarp::os::Bottle &b);
    void    initHistogram();
    int     getHistNum();

};

class SPOTTERModule:public yarp::os::RFModule, public blobSpotter_IDLServer
{
    /* module parameters */
    std::string             moduleName;
    std::string             handlerPortName;
    yarp::os::RpcServer     rpcPort;

    /* pointer to a new thread */
    SPOTTERManager          *spotterManager;
    bool                    closing;

public:

    bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
    bool interruptModule();                       // interrupt, e.g., the ports
    bool close();                                 // close and shut down the module

    bool attach(yarp::os::RpcServer &source);
    
    int  getMinArea();
    bool setMinArea(const int32_t area);
    int  getMaxArea();
    bool setMaxArea(const int32_t area);
    int  getTopBound();
    bool setTopBound(const int32_t area);
    int  newHist();
    int  getTotHist();
    int  getCurHist();
    bool setHist(const int32_t id);
    bool reset();
    bool quit();

    double getPeriod();
    bool updateModule();
};


#endif
//empty line to make gcc happy
