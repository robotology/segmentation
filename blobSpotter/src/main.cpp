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

#include "blobSpotter.h"

using namespace yarp::os;

int main(int argc, char *argv[])
{
    /* initialize yarp network */
    Network yarp;
    if (!yarp.checkNetwork())
        return 1;

    /* prepare and configure the resource finder */
    ResourceFinder rf;
    rf.setVerbose(true);
    rf.configure(argc,argv);

    /* create the module */
    SPOTTERModule module;

    /* run the module: runModule() calls configure first and, if successful, it then runs */
    return module.runModule(rf);
}
//empty line to make gcc happy
