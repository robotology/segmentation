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

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;

/**********************************************************/
bool SPOTTERModule::configure(yarp::os::ResourceFinder &rf)
{
    moduleName = rf.check("name", Value("blobSpotter"), "module name (string)").asString().c_str();
    int minArea = rf.check("minArea", Value(500), "minimum area (int)").asInt();
    int maxArea = rf.check("maxArea", Value(3000), "maximum area (int)").asInt();
    int topBound = rf.check("topBound", Value(30), "top bound (int)").asInt();
    setName(moduleName.c_str());

    handlerPortName =  "/";
    handlerPortName += getName();
    handlerPortName +=  "/rpc:i";

    if (!rpcPort.open(handlerPortName.c_str()))
    {
        fprintf(stdout, "%s : Unable to open port %s\n", getName().c_str(), handlerPortName.c_str());
        return false;
    }

    attach(rpcPort);
    closing = false;

    /* create the thread and pass pointers to the module parameters */
    spotterManager = new SPOTTERManager( moduleName );

    /* now start the thread to do the work */
    spotterManager->open();
    spotterManager->minArea = minArea;
    spotterManager->maxArea = maxArea;
    spotterManager->topBound = topBound;

    return true ;
}

/**********************************************************/
bool SPOTTERModule::interruptModule()
{
    rpcPort.interrupt();
    return true;
}

/**********************************************************/
bool SPOTTERModule::close()
{
    rpcPort.close();
    fprintf(stdout, "starting the shutdown procedure\n");
    spotterManager->interrupt();
    spotterManager->close();
    fprintf(stdout, "deleting thread\n");
    delete spotterManager;
    fprintf(stdout, "done deleting thread\n");
    return true;
}

/************************************************************************/
bool SPOTTERModule::attach(RpcServer &source)
{
    return this->yarp().attachAsServer(source);
}

/**********************************************************/
bool SPOTTERModule::quit()
{
    closing = true;
    return true;
}

/**********************************************************/
int SPOTTERModule::getMaxArea()
{
    return spotterManager->maxArea;
}

/**********************************************************/
bool SPOTTERModule::setMaxArea(const int32_t area)
{
    if (area > spotterManager->minArea && area < 20000)
    {
        spotterManager->maxArea = area;
        return true;
    }else
        return false;
}

/**********************************************************/
int SPOTTERModule::getMinArea()
{
    return spotterManager->minArea;
}

/**********************************************************/
bool SPOTTERModule::setMinArea(const int32_t area)
{
    if (area < spotterManager->maxArea && area > 1)
    {
        spotterManager->minArea = area;
        return true;
    }else
        return false;
}

/**********************************************************/
int SPOTTERModule::getTopBound()
{
    return spotterManager->topBound;
}

/**********************************************************/
bool SPOTTERModule::setTopBound(const int32_t topBound)
{
    if (topBound < 240 && topBound > 1)
    {
        spotterManager->topBound = topBound;
        return true;
    }else
        return false;
}

/**********************************************************/
int SPOTTERModule::getTotHist()
{
    return spotterManager->histCnt;
}

/**********************************************************/
int SPOTTERModule::getCurHist()
{
    return spotterManager->histIndex + 1;
}

/**********************************************************/
int SPOTTERModule::newHist()
{
    printf("ROI after is %lu\n",spotterManager->roi.size());
    spotterManager->roi.clear();
    printf("ROI after is %lu\n",spotterManager->roi.size());
    spotterManager->isInitialised = false;
    int rep = spotterManager->getHistNum();
    return rep;
}

/**********************************************************/
bool SPOTTERModule::setHist(const int index)
{
    int rep = spotterManager->getHistNum();

    if (index > 0 && index <= rep)
    {
        spotterManager->mutex.wait();
        spotterManager->histIndex = index - 1;
        spotterManager->mutex.post();
        return true;
    }
    else
        return false;
}

/**********************************************************/
bool SPOTTERModule::reset()
{
    //to be conpleted
    return true;
}

/**********************************************************/
bool SPOTTERModule::updateModule()
{
    return !closing;
}

/**********************************************************/
double SPOTTERModule::getPeriod()
{
    return 0.1;
}

/**********************************************************/
SPOTTERManager::~SPOTTERManager()
{

}

/**********************************************************/
SPOTTERManager::SPOTTERManager( const string &moduleName )
{
    fprintf(stdout,"initialising Variables\n");
    this->moduleName = moduleName;
    roiPoints.setManager(this);
    deleted = false;
}

/**********************************************************/
int SPOTTERManager::getHistNum()
{
    return histCnt;
}

/**********************************************************/
bool SPOTTERManager::open()
{
    this->useCallback();

    //create all ports
    inImgPortName = "/" + moduleName + "/image:i";
    BufferedPort<ImageOf<PixelRgb> >::open( inImgPortName.c_str() );

    inRoiPortName = "/" + moduleName + "/fixRoi:i";
    roiPoints.open( inRoiPortName.c_str() );

    outImgOrigPortName = "/" + moduleName + "/propagated:o";
    imageOrigPort.open( outImgOrigPortName.c_str() );

    outImgPortName = "/" + moduleName + "/image:o";
    imageOutPort.open( outImgPortName.c_str() );

    outTargetPortName = "/" + moduleName + "/blobs:o";
    targetOutPort.open( outTargetPortName.c_str() );

    isInitialised=false;
    time = 0;
    histCnt = 0;
    histIndex = 0;
    histParams = new histDetails [MAX_HISTS];

    return true;
}

/**********************************************************/
void SPOTTERManager::close()
{
    mutex.wait();
    fprintf(stdout,"now closing ports...\n");
    imageOutPort.writeStrict();
    imageOutPort.close();
    targetOutPort.writeStrict();
    targetOutPort.close();
    roiPoints.close();
    imageOrigPort.close();
    BufferedPort<ImageOf<PixelRgb> >::close();
    mutex.post();
    fprintf(stdout,"finished closing the read port...\n");
}

/**********************************************************/
void SPOTTERManager::interrupt()
{
    fprintf(stdout,"cleaning up...\n");
    fprintf(stdout,"attempting to interrupt ports\n");
    roiPoints.interrupt();
    BufferedPort<ImageOf<PixelRgb> >::interrupt();
    fprintf(stdout,"finished interrupt ports\n");
}

/**********************************************************/
void SPOTTERManager::processRoiPoints(Bottle &b)
{
    if (b.get(0).asDouble() < 1 || b.get(1).asDouble() < 1)
        fprintf(stdout,"error in the fixation point, ignoring it\n");
    else
    {
        cv::Point2f tmp;
        tmp.x = (float)b.get(0).asDouble();
        tmp.y = (float)b.get(1).asDouble();

        printf("Points are: %f and %f \n", tmp.x, tmp.y);
        roi.push_back(tmp);
    }
}

/**********************************************************/
void SPOTTERManager::initHistogram()
{
    histParams[histCnt].rect = cv::Rect((int)roi[0].x,(int)roi[0].y,(int)(roi[1].x-roi[0].x),(int)(roi[1].y-roi[0].y));
    cv::Mat  tmp = histParams[histCnt].hc.colorReduce(imgMat, 32);
    imageROI = tmp(histParams[histCnt].rect); // table area
    histParams[histCnt].shist.release();
    histParams[histCnt].shist = histParams[histCnt].hc.getSparseHistogram(imageROI);//getSparseHistogram(imageROI);
    histParams[histCnt].finder.setHistogram(histParams[histCnt].shist);
    histParams[histCnt].finder.setThreshold(0.0001f);
    histCnt++;
    isInitialised = true;
}

/**********************************************************/
void SPOTTERManager::onRead(ImageOf<yarp::sig::PixelRgb> &img)
{
    yarp::os::Stamp ts;
    roiPoints.getEnvelope(ts);

    ImageOf<PixelRgb> &outImg  = imageOutPort.prepare();
    //ImageOf<PixelMono> &outImg  = imageOutPort.prepare();
    ImageOf<PixelRgb> &outOrig = imageOrigPort.prepare();
    outImg.resize(img.width(), img.height());
    outImg.zero();
    imgMat = cv::cvarrToMat((IplImage*)img.getIplImage());
    cv::Mat drawing = cv::Mat::zeros( imgMat.size(), CV_8UC3 );

    Bottle &b = targetOutPort.prepare();
    b.clear();

    if (!isInitialised)
    {
        if ( roi.size()>1 )
        {
            for (size_t i = 0; i<roi.size(); i++)
                printf("GOT info  %f and %f \n", roi[i].x, roi[i].y);

            initHistogram();
        }
        else if (roi.size() == 1)
        {
            line( imgMat, cv::Point2f(roi[0].x,roi[0].y), cv::Point2f(roi[0].x,roi[0].y+15), cvScalar( 255, 255, 255 ), 2, 8 );
            line( imgMat, cv::Point2f(roi[0].x,roi[0].y), cv::Point2f(roi[0].x+15,roi[0].y), cvScalar( 255, 255, 255 ), 2, 8 );
            cv::circle( imgMat, cv::Point2f(roi[0].x,roi[0].y), 3, cvScalar(0,0,255), -1, 8, 0 );
        }
    }
    else
    {
        mutex.wait();

        if (time <30)
        {
            line( imgMat, cv::Point2f(roi[0].x,roi[0].y), cv::Point2f(roi[0].x,roi[0].y+15), cvScalar( 255, 255, 255 ), 2, 8 );
            line( imgMat, cv::Point2f(roi[0].x,roi[0].y), cv::Point2f(roi[0].x+15,roi[0].y), cvScalar( 255, 255, 255 ), 2, 8 );
            cv::circle( imgMat, cv::Point2f(roi[0].x,roi[0].y), 3, cvScalar(0,0,255), -1, 8, 0 );

            line( imgMat, cv::Point2f(roi[1].x,roi[1].y), cv::Point2f(roi[1].x,roi[1].y-15), cvScalar( 255, 255, 255 ), 2, 8 );
            line( imgMat, cv::Point2f(roi[1].x,roi[1].y), cv::Point2f(roi[1].x-15,roi[1].y), cvScalar( 255, 255, 255 ), 2, 8 );
            cv::circle( imgMat, cv::Point2f(roi[1].x,roi[1].y), 3, cvScalar(0,0,255), -1, 8, 0 );
            time ++;
        }

        cv::Mat tmp = histParams[histIndex].hc.colorReduce(imgMat, 32);
        // Get back-projection of color histogram
        result = histParams[histIndex].finder.find(tmp);

        // Invert colours
        bitwise_not(result, result);

        // Thresholding on the image
        threshold(result, result, 100, 255.0, cv::THRESH_BINARY);

        // Apply some gaussian blur using the specified Kernel
        GaussianBlur(result, result, cv::Size(9, 9), 2.0, 2.0 );

        // Noise removal - Remove any pixel that do not belong to the object...
        uint8_t* pixelPtr = (uint8_t*)result.data;
        int cn = result.channels();
        for(int i = 0; i < result.rows; i++)
        {
            for(int j = 0; j < result.cols; j += cn)
            {
                cv::Scalar_<uint8_t> bgrPixel;
                bgrPixel.val[0] = pixelPtr[i*result.cols*cn + j*cn + 0];

                if (bgrPixel.val[0] < 200)
                    pixelPtr[i*result.cols*cn + j*cn + 0] = 0;
            }
        }
        cv::Mat test;
        result.copyTo(test);

        vector<vector<cv::Point> > cnt;
        vector<cv::Vec4i> hrch;

        // Find contours
        findContours( test, cnt, hrch, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
        //findContours( test, cnt, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1);
        // Get the moments
        vector<cv::Moments> mu(cnt.size() );
        for( size_t i = 0; i < cnt.size(); i++ )
            mu[i] = moments( cnt[i], false );

        // Get the mass centers:
        vector<cv::Point2f> mc( cnt.size() );
        vector<cv::Point2f> mcSel;

        for( size_t i = 0; i < cnt.size(); i++ )
            mc[i] = cv::Point2f( (float)(mu[i].m10/mu[i].m00) , (float)(mu[i].m01/mu[i].m00) );

        vector<vector<cv::Point> > knownCnts(cnt.size());
        // Draw contours for contours bigget than a defined area and smaller than another
        //printf("\t Info: Area and Contour Length \n");

        int numCnt = 0;

        vector<vector<cv::Point> > contours_poly( cnt.size() );
        vector<cv::Rect> boundRect( cnt.size() );

        for( size_t i = 0; i< cnt.size(); i++ )
        {
            if (mu[i].m00 > minArea &&  mu[i].m00 < maxArea && mc[i].y > topBound)
            {
                //printf(" * Contour[%d] -X[%lf]  -Y[%lf] -Area  = %.2f -Area OpenCV: %.2f -Length: %.2f \n", i, mc[i].x, mc[i].y, mu[i].m00, contourArea(cnt[i]), arcLength( cnt[i], true ) );

                cv::drawContours( drawing, cnt, i, cvScalar(255,255,255), 2, 8, hrch, 0, cv::Point() );
                //cv::circle( drawing, mc[i], 3, cvScalar(0,0,255), -1, 8, 0 );
                mcSel.push_back(mc[i]);
                //std::string s = std::to_string(numCnt);
                //putText(drawing, s, cv::Point(mc[i].x,mc[i].y-10), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,0,0), 1, CV_AA);
                knownCnts[numCnt] = cnt[i];
                numCnt++;
                approxPolyDP( cv::Mat(cnt[i]), contours_poly[i], 3, true );
                boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
                //cv::floodFill(drawing, mc[i], cv::Scalar(255,255,255) ,0, cv::Scalar(), cv::Scalar(), 4);
                //rectangle( result, boundRect[i].tl(), boundRect[i].br(), cvScalar(255,255,255), 2, 8, 0 );

                Bottle &t=b.addList();
                t.addDouble(boundRect[i].tl().x);
                t.addDouble(boundRect[i].tl().y);
                t.addDouble(boundRect[i].br().x);
                t.addDouble(boundRect[i].br().y);
            }
        }

        if (b.size())
        {
            targetOutPort.setEnvelope(ts);
            targetOutPort.write();
        }

        mutex.post();
    }

    IplImage processed = drawing;
    outImg.resize(processed.width, processed.height);
    cvCopy( &processed, (IplImage *) outImg.getIplImage());
    imageOutPort.setEnvelope(ts);
    imageOutPort.write();

    IplImage orig = imgMat;
    outOrig.resize(orig.width, orig.height);
    cvCopy( &orig, (IplImage *) outOrig.getIplImage());
    imageOrigPort.setEnvelope(ts);
    imageOrigPort.write();

}
//empty line to make gcc happy
