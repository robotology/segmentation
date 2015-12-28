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

#include <yarp/os/Time.h>

#include "utils.h"
#include "blobSpotter.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;

/**********************************************************/
ROIPoints::ROIPoints()
{
    manager=NULL;
    useCallback();
}

/**********************************************************/
void ROIPoints::setManager(SPOTTERManager *manager)
{
    this->manager=manager;
}

/**********************************************************/
void ROIPoints::onRead(Bottle &target)
{
    if (target.size()>1)
        manager->processRoiPoints(target);
}