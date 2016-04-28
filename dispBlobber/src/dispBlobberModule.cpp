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
#include "dispBlobberModule.hpp"

using namespace cv;
using namespace std;
using namespace yarp::os;
using namespace yarp::sig;


bool DispBlobberModule::configure(yarp::os::ResourceFinder &rf)
{
    moduleName = rf.check("name", Value("dispBlobber"), "module name (string)").asString();

    setName(moduleName.c_str());

    handlerPortName =  "/";
    handlerPortName += getName();
    handlerPortName +=  "/rpc:i";

    if (!handlerPort.open(handlerPortName.c_str()))    {
        fprintf(stdout, "%s : Unable to open RPC port %s\n", getName().c_str(), handlerPortName.c_str());
        return false;
    }
    attach(handlerPort);

    blobPort = new DispBlobberPort( moduleName, rf );

    blobPort->open();

    closing = false;

    return true ;
}

bool DispBlobberModule::interruptModule()
{
    closing = true;

    handlerPort.interrupt();

    blobPort->interrupt();

    return true;
}

bool DispBlobberModule::close()
{
    handlerPort.close();

    fprintf(stdout, "starting the shutdown procedure\n");   

    blobPort->close();

    fprintf(stdout, "deleting thread\n");
    delete blobPort;
    fprintf(stdout, "done deleting thread\n");

    return true;
}

bool DispBlobberModule::updateModule()
{
    return !closing;
}

bool DispBlobberModule::respond(const Bottle &command, Bottle &reply)
{

    reply.clear();

    /* Get command string */
    string receivedCmd = command.get(0).asString().c_str();

    int responseCode;   // contain Vocab-encoded response

    if (receivedCmd == "margin")
    {
        bool ok = blobPort->setMargin(command.get(1).asInt());
        if (ok)
            responseCode = Vocab::encode("ack");
            else
            {
                fprintf(stdout,"Margin for ROI cannot be set. \n");
                responseCode = Vocab::encode("nack");
            }
        reply.addVocab(responseCode);
        return true;
    }
    if (receivedCmd == "thresh")
    {
        bool ok = blobPort->setThresh(command.get(1).asInt());
        if (ok)
            responseCode = Vocab::encode("ack");
        else {
            fprintf(stdout,"Threshold cannot be set. \n");
            responseCode = Vocab::encode("nack");
        }
        reply.addVocab(responseCode);
        return true;
    }
    else if (receivedCmd == "help")
    {
        reply.addVocab(Vocab::encode("many"));

        responseCode = Vocab::encode("ack");

        reply.addString("Available commands are:");
        reply.addString("margin (int) - sets the margin (in pixels) that the ROI keeps around the closest blob.");
        reply.addString("thresh (int) - sets lower luminosity limit (0-255) that is considered. Objects with luminosity lower than the boundary wont be considered.");
        reply.addString("help - produces this help.");
        reply.addString("quit - closes the module.");
        
        reply.addVocab(responseCode);
        return true;
    }
    else if (receivedCmd == "quit")
    {
        responseCode = Vocab::encode("ack");

        reply.addVocab(responseCode);

        closing = true;
        return true;
    }
    
    reply.addString("Invalid command, type [help] for a list of accepted commands.");
    
    return true;
}

double DispBlobberModule::getPeriod()
{
    return 0.1;
}

DispBlobberPort::DispBlobberPort( const string &_moduleName, ResourceFinder &rf)
{

    this->moduleName = _moduleName;

    moduleRF = &rf;

    fprintf(stdout,"Parsing parameters...\n");

    int imH = moduleRF->check("imH", Value(240)).asInt();
    int imW = moduleRF->check("imW", Value(320)).asInt();

    int bufferSize = moduleRF->check("bufferSize", Value(1)).asInt();

    int margin = moduleRF->check("margin", Value(20)).asInt();
    cropSize = 0;

    if (rf.check("cropSize"))
    {
        Value &vCropSize=rf.find("cropSize");

        if (!vCropSize.isString())
        {
            cropSize = vCropSize.asInt();
            margin = 0; // not used in this case
        }
    }

    // threshold of intensity of the image under which info is ignored
    int backgroundThresh = moduleRF->check("backgroundThresh", Value(30)).asInt();
   
    int minBlobSize = moduleRF->check("minBlobSize", Value(300)).asInt();

    int gaussSize = moduleRF->check("gaussSize", Value(5)).asInt();

    int imageThreshRatioLow = moduleRF->check("imageThreshRatioLow", Value(10)).asInt();
    int imageThreshRatioHigh = moduleRF->check("imageThreshRatioHigh", Value(20)).asInt();

    blobExtractor = NULL;

    blobExtractor = new dispBlobber(imH, imW, bufferSize,
            margin,
            backgroundThresh,
            minBlobSize, gaussSize,
            imageThreshRatioLow, imageThreshRatioHigh);
}

bool DispBlobberPort::open()
{

    this->useCallback();

    fprintf(stdout,"Opening ports...\n");

    /* Inputs */

    imgInPortName = "/" + moduleName + "/img:i";
    BufferedPort<ImageOf<PixelBgr>  >::open( imgInPortName.c_str() );

    /* Outputs */

    blobsOutPortName = "/" + moduleName + "/blobs/left:o";
    blobsOutPort.open(blobsOutPortName);

    blobsOutPortRightName = "/" + moduleName + "/blobs/right:o";
    blobsOutPortRight.open(blobsOutPortRightName);

    points3dOutPortName = "/" + moduleName + "/points3d:o";;
    points3dOutPort.open(points3dOutPortName);

    roiOutPortName = "/" + moduleName + "/roi/left:o";
    roiOutPort.open(roiOutPortName);

    roiOutPortRightName = "/" + moduleName + "/roi/right:o";
    roiOutPortRight.open(roiOutPortRightName);

    optOutPortName = "/" + moduleName + "/opt:o";
    optOutPort.open(optOutPortName);
    
    cropOutPortName = "/" + moduleName + "/crop:o";
    cropOutPort.open(cropOutPortName);

    sfmRpcPort.open(("/" + moduleName + "/sfm/rpc").c_str());

    return true;
}

void DispBlobberPort::close()
{
    fprintf(stdout,"Closing ports...\n");

    blobsOutPort.close();
    blobsOutPortRight.close();
    points3dOutPort.close();

    roiOutPort.close();
    roiOutPortRight.close();
    
    optOutPort.close();
    cropOutPort.close();

    sfmRpcPort.close();

    BufferedPort<ImageOf<PixelBgr>  >::close();
            
    fprintf(stdout,"Finished closing ports...\n");
}

void DispBlobberPort::interrupt()
{   
   
    fprintf(stdout,"Attempting to interrupt ports...\n");

    blobsOutPort.interrupt();
    blobsOutPortRight.interrupt();
    points3dOutPort.interrupt();

    roiOutPort.interrupt();
    roiOutPortRight.interrupt();

    optOutPort.interrupt();
    cropOutPort.interrupt();

    sfmRpcPort.interrupt();

    BufferedPort<ImageOf<PixelBgr>  >::interrupt();
    
    fprintf(stdout,"Finished interrupting ports...\n");
}

bool DispBlobberPort::setThresh(int low)
{
    return blobExtractor->setThresh(low);

}

bool DispBlobberPort::setMargin(int mrg)
{
    return blobExtractor->setMargin(mrg);
}

void DispBlobberPort::onRead(ImageOf<PixelBgr> &input)
{
    mutex.wait();

    /* Get the envelope from the input image */

    Stamp stamp;
    BufferedPort<ImageOf<PixelBgr>  >::getEnvelope(stamp);

    /* Prepare output data structures */

    std::vector<int> centroid;
    std::vector<int> roi;
    cv::Mat blobMat;

    /* Prepare the buffer, call the extractor, clear the buffer */

    cv::Mat inputMat=cv::cvarrToMat((IplImage*)input.getIplImage());
    imagesMatBuffer.push_back(inputMat);

    double blobSize = blobExtractor->extractBlob(imagesMatBuffer, roi, centroid, blobMat);

    if (blobSize>0)
    {

        if (optOutPort.getOutputCount()>0)
        {
            yarp::sig::ImageOf<yarp::sig::PixelMono> &blobImage = optOutPort.prepare();
            blobImage.resize(blobMat.cols, blobMat.rows);

            cv::Mat blobImageMat=cv::cvarrToMat((IplImage*)blobImage.getIplImage());
            blobMat.copyTo(blobImageMat);

            optOutPort.setEnvelope(stamp);
            optOutPort.write();
        }

        int x = centroid[0];
        int y = centroid[1];

        int dx = ( (cropSize>0) ? cropSize : (roi[2]-roi[0]) );
        int dy = ( (cropSize>0) ? cropSize : (roi[3]-roi[1]) );

        int dx2 = dx>>1;
        int dy2 = dy>>1;

        int tlx = std::max(x-dx2,0);
        int tly = std::max(y-dy2,0);
        int brx = std::min(x+dx2,blobMat.cols-1);
        int bry = std::min(y+dy2,blobMat.rows-1);

        if (cropOutPort.getOutputCount()>0)
        {
            cv::Rect roiRegion = cv::Rect(cv::Point( tlx, tly ), cv::Point( brx, bry ));

            yarp::sig::ImageOf<yarp::sig::PixelBgr> &cropImage = cropOutPort.prepare();
            cropImage.resize(roiRegion.width, roiRegion.height);

            cv::Mat cropImageMat=cv::cvarrToMat((IplImage*)cropImage.getIplImage());
            imagesMatBuffer.back()(roiRegion).copyTo(cropImageMat);

            cropOutPort.setEnvelope(stamp);
            cropOutPort.write();
        }

        if (roiOutPort.getOutputCount()>0)
        {
            Bottle roisBottle;

            Bottle &roiBottle = roisBottle.addList();
            roiBottle.addInt(tlx);
            roiBottle.addInt(tly);
            roiBottle.addInt(brx);
            roiBottle.addInt(bry);

            roiOutPort.prepare() = roisBottle;

            roiOutPort.setEnvelope(stamp);
            roiOutPort.write();
        }

        if (blobsOutPort.getOutputCount()>0)
        {
            Bottle blobsBottle;

            Bottle &blobBottle = blobsBottle.addList();
            blobBottle.addInt(centroid[0]);
            blobBottle.addInt(centroid[1]);
            blobBottle.addInt((int)(blobSize+0.5f));

            blobsOutPort.prepare() = blobsBottle;

            blobsOutPort.setEnvelope(stamp);
            blobsOutPort.write();
        }

        if (roiOutPortRight.getOutputCount()>0)
        {
            Bottle cmd_sfm, reply_sfm;

            cmd_sfm.addInt(tlx);
            cmd_sfm.addInt(tly);
            sfmRpcPort.write(cmd_sfm,reply_sfm);

            Bottle roisBottle;
            Bottle &roiBottle = roisBottle.addList();

            if (reply_sfm.size()>0)
            {
                double tlX = reply_sfm.get(0).asDouble();
                double tlY = reply_sfm.get(1).asDouble();
                double tlZ = reply_sfm.get(2).asDouble();

                if (!(tlX==0 && tlY==0 && tlZ==0))
                {
                    int tlur = reply_sfm.get(3).asInt();
                    int tlvr = reply_sfm.get(4).asInt();

                    roiBottle.addInt(tlur);
                    roiBottle.addInt(tlvr);
                }
            }

            cmd_sfm.clear();
            reply_sfm.clear();

            cmd_sfm.addInt(brx);
            cmd_sfm.addInt(bry);
            sfmRpcPort.write(cmd_sfm,reply_sfm);

            if (reply_sfm.size()>0)
            {
                double brX = reply_sfm.get(0).asDouble();
                double brY = reply_sfm.get(1).asDouble();
                double brZ = reply_sfm.get(2).asDouble();

                if (!(brX==0 && brY==0 && brZ==0))
                {
                    int brur = reply_sfm.get(3).asInt();
                    int brvr = reply_sfm.get(4).asInt();

                    roiBottle.addInt(brur);
                    roiBottle.addInt(brvr);
                }
            }

            if (roiBottle.size()>0)
            {
                roiOutPortRight.prepare() = roisBottle;
                roiOutPortRight.setEnvelope(stamp);
                roiOutPortRight.write();
            }

        }

        if (blobsOutPortRight.getOutputCount()>0 || points3dOutPort.getOutputCount()>0)
        {
            Bottle cmd_sfm, reply_sfm;

            cmd_sfm.addInt(centroid[0]);
            cmd_sfm.addInt(centroid[1]);
            sfmRpcPort.write(cmd_sfm,reply_sfm);

            if (reply_sfm.size()>0)
            {
                double X = reply_sfm.get(0).asDouble();
                double Y = reply_sfm.get(1).asDouble();
                double Z = reply_sfm.get(2).asDouble();

                if (points3dOutPort.getOutputCount()>0)
                {
                    Bottle points3dBottle;
                    Bottle &point3dBottle = points3dBottle.addList();

                    point3dBottle.addDouble(X);
                    point3dBottle.addDouble(Y);
                    point3dBottle.addDouble(Z);

                    points3dOutPort.prepare() = points3dBottle;
                    points3dOutPort.setEnvelope(stamp);
                    points3dOutPort.write();
                }

                if (blobsOutPort.getOutputCount()>0)
                {
                    if (!(X==0.0 && Y==0.0 && Z==0.0))
                    {
                        int ur = reply_sfm.get(3).asInt();
                        int vr = reply_sfm.get(4).asInt();

                        Bottle blobsBottle;
                        Bottle &blobBottle = blobsBottle.addList();

                        blobBottle.addInt(ur);
                        blobBottle.addInt(vr);

                        blobsOutPortRight.prepare() = blobsBottle;
                        blobsOutPortRight.setEnvelope(stamp);
                        blobsOutPortRight.write();
                    }
                }
            }
        }

    }

    imagesMatBuffer.erase(imagesMatBuffer.begin());

    mutex.post();

}

