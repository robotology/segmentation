/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Vadim Tikhanoff
 * email:   vadim.tikhanoff@iit.it
 * website: www.robotcub.org
 * Algorithm taken from R. Hess, A. Fern, "Discriminatively trained particle filters for complex multi-object tracking,"
 * cvpr, pp.240-247, 2009 IEEE Conference on Computer Vision and Pattern Recognition, 2009
 *
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


#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

#include <yarp/os/Bottle.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/PortReport.h>
#include <yarp/os/Stamp.h>
#include <yarp/os/Semaphore.h>
#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>
#include <yarp/os/Event.h>

#include <cv.h>
#include <highgui.h>

class SPOTTERManager;  //forward declaration

/**********************************************************/
class ROIPoints : public yarp::os::BufferedPort<yarp::os::Bottle>
{
protected:
    SPOTTERManager *manager;
    void onRead(yarp::os::Bottle &b);
public:
    ROIPoints();
    void setManager(SPOTTERManager *manager);
};

#endif
