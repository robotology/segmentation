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

#include "lbpExtract.h"

using namespace yarp::sig;

/**********************************************************/
bool SEGMENTModule::configure(yarp::os::ResourceFinder &rf){
    moduleName = rf.check("name", yarp::os::Value("lbpExtract"), "module name (string)").asString();

    setName(moduleName.c_str());

    handlerPortName =  "/";
    handlerPortName += getName();
    handlerPortName +=  "/rpc:i";

    if (!rpcPort.open(handlerPortName.c_str())){
        fprintf(stdout, "%s : Unable to open port %s\n", getName().c_str(), handlerPortName.c_str());
        return false;
    }

    attach(rpcPort);
    closing = false;

    /* create the thread and pass pointers to the module parameters */
    segmentManager = new SEGMENTManager( moduleName );

    int rad     = rf.check("radius",yarp::os::Value(5)).asInt();
    int iter    = rf.check("numIteration",yarp::os::Value(5)).asInt();
    int neigh   = rf.check("neighbours",yarp::os::Value(8)).asInt();
    int topB    = rf.check("topBound",yarp::os::Value(40)).asInt();
    int minA    = rf.check("minArcLength",yarp::os::Value(75)).asInt();
    int maxA    = rf.check("maxArcLength",yarp::os::Value(400)).asInt();
    
    segmentManager->setDefaultValues(rad, neigh, topB, minA, maxA, iter);
    
    /* now start the thread to do the work */
    segmentManager->open();
    
    return true ;
}

/**********************************************************/
bool SEGMENTModule::interruptModule(){
    rpcPort.interrupt();
    return true;
}

/**********************************************************/
bool SEGMENTModule::close(){
    rpcPort.close();
    yDebug("starting the shutdown procedure\n");
    segmentManager->interrupt();
    segmentManager->close();
    yDebug("deleting thread\n");
    delete segmentManager;
    yDebug("done deleting thread\n");
    return true;
}

/************************************************************************/
bool SEGMENTModule::attach(yarp::os::RpcServer &source){
    return this->yarp().attachAsServer(source);
}

/**********************************************************/
bool SEGMENTModule::quit(){
    closing = true;
    return true;
}

/**********************************************************/
bool SEGMENTModule::reset(){
    //to be conpleted
    return true;
}

/**********************************************************/
bool SEGMENTModule::updateModule(){
    return !closing;
}

/**********************************************************/
double SEGMENTModule::getPeriod(){
    return 0.1;
}

/**********************************************************/
bool SEGMENTModule::setRadius(const int32_t radius){
    segmentManager->setRadius(radius);
    return true;
}

/**********************************************************/
bool SEGMENTModule::setNeighbours(const int32_t neighbours){
    segmentManager->setNeighbours(neighbours);
    return true;
}

/**********************************************************/
bool SEGMENTModule::setTopBound(const int32_t topBound){
    segmentManager->setTopBound(topBound);
    return true;
}

/**********************************************************/
bool SEGMENTModule::setMinArcLength(const int32_t minArcLenght){
    segmentManager->setMinArcLength(minArcLenght);
    return true;
}

/**********************************************************/
bool SEGMENTModule::setMaxArcLength(const int32_t maxArcLenght){
    segmentManager->setMaxArcLength(maxArcLenght);
    return true;
}

/**********************************************************/
bool SEGMENTModule::setNumIteration(const int32_t numIteration){
    segmentManager->setNumIteration(numIteration);
    return true;
}

/**********************************************************/
bool SEGMENTModule::resetAllValues(){
    
    segmentManager->resetAllValues();
    return true;
}

/**********************************************************/
int SEGMENTModule::getRadius(){
    return segmentManager->getRadius();
}

/**********************************************************/
int SEGMENTModule::getNeighbours(){
    return segmentManager->getNeighbours();
}

/**********************************************************/
int SEGMENTModule::getTopBound(){
    return segmentManager->getTopBound();
}

/**********************************************************/
int SEGMENTModule::getMinArcLength(){
    return segmentManager->getMinArcLength();
}

/**********************************************************/
int SEGMENTModule::getMaxArcLength(){
    return segmentManager->getMaxArcLength();
}

/**********************************************************/
int SEGMENTModule::getNumIteration(){
    return segmentManager->getNumIteration();
}

/**********************************************************/
yarp::os::Bottle SEGMENTModule::get_component_around(const int32_t x, const int32_t y){
    return segmentManager->get_component_around(x, y);
}

/**********************************************************/
SEGMENTManager::~SEGMENTManager(){

}

/**********************************************************/
SEGMENTManager::SEGMENTManager( const std::string &moduleName ){
    fprintf(stdout,"initialising Variables\n");
    this->moduleName = moduleName;
}

/**********************************************************/
bool SEGMENTManager::setDefaultValues(const int32_t radius, const int32_t neighbours, const int32_t topBound, const int32_t minArcLength, const int32_t maxArcLength, const int32_t numIteration){
    
    defaultRadius       = radius;
    defaultNeighbours   = neighbours;
    defaultTopBound     = topBound;
    defaultMinArcLength = minArcLength;
    defaultMaxArcLength = maxArcLength;
    defaultNumIteration = numIteration;

    return true;
}

/**********************************************************/
bool SEGMENTManager::open(){
    this->useCallback();

    //create all ports
    inPortName = "/" + moduleName + "/image:i";
    BufferedPort<ImageOf<PixelRgb> >::open( inPortName.c_str() );

    outPortPropagate.open( "/" + moduleName + "/propagated:o" );
    outPortBlobs.open( "/" + moduleName + "/extractedlbp:o" );
    outPortSegmented.open( "/" + moduleName + "/segmentedlbp:o" );
    outTargetPort.open( "/" + moduleName + "/blobs:o" );
    outPortLbp.open( "/" + moduleName + "/lbp:o" );
    outPortLbpContours.open( "/" + moduleName + "/contourslbp:o" );
    
    radius = defaultRadius;
    neighbours = defaultNeighbours;
    minArcLength = defaultMinArcLength;
    maxArcLength = defaultMaxArcLength;
    topBound = defaultTopBound;
    numIteration = defaultNumIteration;
    
    yInfo("Module started with the following default values:\nradius: %d, neighbours %d, minArcLength %d, maxArcLength, %d, topBound %d, numIteration %d", radius, neighbours, minArcLength, maxArcLength, topBound, numIteration);
    
    return true;
}

/**********************************************************/
void SEGMENTManager::close(){
    
    yDebug("now closing ports...\n");
    
    outPortPropagate.close();
    outPortBlobs.close();
    outPortSegmented.close();
    outPortLbp.close();
    outPortLbpContours.close();
    outTargetPort.close();
    
    BufferedPort<ImageOf<PixelRgb> >::close();
    
    yDebug("finished closing the read port...\n");
}

/**********************************************************/
void SEGMENTManager::interrupt(){
    yDebug("cleaning up...\n");
    yDebug("attempting to interrupt ports\n");
    BufferedPort<ImageOf<PixelRgb> >::interrupt();

    yDebug("finished interrupt ports\n");
}

/**********************************************************/
bool SEGMENTManager::setRadius(const int32_t radius){
    this->radius = radius;
    return true;
}

/**********************************************************/
bool SEGMENTManager::setNeighbours(const int32_t neighbours){
    this->neighbours = neighbours;
    return true;
}

/**********************************************************/
bool SEGMENTManager::setTopBound(const int32_t topBound){
    this->topBound = topBound;
    return true;
}

/**********************************************************/
bool SEGMENTManager::setMinArcLength(const int32_t minArcLength){
    this->minArcLength = minArcLength;
    return true;
}

/**********************************************************/
bool SEGMENTManager::setMaxArcLength(const int32_t maxArcLength){
    this->maxArcLength = maxArcLength;
    return true;
}

/**********************************************************/
bool SEGMENTManager::setNumIteration(const int32_t numIteration){
    this->numIteration = numIteration;
    return true;
}

/**********************************************************/
bool SEGMENTManager::resetAllValues(){
    radius = defaultRadius;
    neighbours = defaultNeighbours;
    topBound = defaultTopBound;
    minArcLength = defaultMinArcLength;
    maxArcLength = defaultMaxArcLength;
    return true;
}

/**********************************************************/
int SEGMENTManager::getRadius(){
    return this->radius;
}

/**********************************************************/
int SEGMENTManager::getNeighbours(){
    return this->neighbours;
}

/**********************************************************/
int SEGMENTManager::getTopBound(){
    return this->topBound;
}

/**********************************************************/
int SEGMENTManager::getMinArcLength(){
    return this->minArcLength;
}

/**********************************************************/
int SEGMENTManager::getMaxArcLength(){
    return this->maxArcLength;
}

/**********************************************************/
int SEGMENTManager::getNumIteration(){
    return this->numIteration;
}

/**********************************************************/
yarp::os::Bottle SEGMENTManager::get_component_around(const int32_t x, const int32_t y){

    yarp::os::Bottle& tosend = getComponents(segmented, x, y);
    
    return tosend;
}

/**********************************************************/
yarp::os::Bottle& SEGMENTManager::getComponents(cv::Mat &img, int x, int y)
{
    allPoints.clear();
    
    std::vector<std::vector<cv::Point> > objcnt;
    std::vector<cv::Vec4i> objhrch;
    cv::Mat prov;
    semComp.lock();
    
    if (img.rows == 0 || img.cols == 0){
        return allPoints;
    }
    
    cvtColor(img, prov, CV_BGR2GRAY);
    
    findContours( prov, objcnt, objhrch, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );
    
    semComp.unlock();
    
    cv::Mat nonZeroCoordinates;
    cv::Mat inside = cv::Mat::zeros( imgMat.size(), CV_8UC1 );
    
    for( size_t i = 0; i< objcnt.size(); i++ )
    {
        if (pointPolygonTest( objcnt[i], cv::Point2f(x, y), 1 ) > 0)
            cv::drawContours( inside, objcnt, i, cvScalar(255,255,355), CV_FILLED, 8, objhrch, 0, cv::Point() );
    }
    
    cv::findNonZero(inside, nonZeroCoordinates);
    
    for (size_t i = 0; i < nonZeroCoordinates.total(); i++ ) {
        yarp::os::Bottle &subjList = allPoints.addList();
        subjList.addInt(nonZeroCoordinates.at<cv::Point>(i).x);
        subjList.addInt(nonZeroCoordinates.at<cv::Point>(i).y);
    }

    return allPoints;
}
/**********************************************************/
void SEGMENTManager::onRead(ImageOf<yarp::sig::PixelRgb> &img){
    yarp::os::Stamp ts;

    ImageOf<PixelRgb>   &outOrig            = outPortPropagate.prepare();
    ImageOf<PixelRgb>   &outImg             = outPortBlobs.prepare();
    ImageOf<PixelRgb>   &outSeg             = outPortSegmented.prepare();
    ImageOf<PixelMono>  &outLbp             = outPortLbp.prepare();
    ImageOf<PixelMono>  &outLbpContour      = outPortLbpContours.prepare();
    
    outOrig.resize(img.width(), img.height());
    outImg.resize(img.width(), img.height());
    outSeg.resize(img.width(), img.height());
    outLbp.resize(img.width(), img.height());
    outLbpContour.resize(img.width(), img.height());
    
    outOrig.zero();
    outImg.zero();
    outSeg.zero();
    outLbp.zero();
    outLbpContour.zero();
    
    imgMat = (IplImage*)img.getIplImage();

    yarp::os::Bottle &b = outTargetPort.prepare();
    b.clear();
    
    cv::Mat temp;
    cv::Mat lbp = cv::Mat::zeros( imgMat.size(), CV_8UC1 );
    cv::Mat extracted = cv::Mat::zeros( imgMat.size(), CV_8UC3 );
    
    semComp.lock();
    segmented = cv::Mat::zeros( imgMat.size(), CV_8UC3 );

    cvtColor(imgMat, temp, CV_BGR2GRAY);
    //GaussianBlur(temp, temp, cv::Size(3,3), 5, 3, BORDER_CONSTANT); // tiny bit of smoothing is always a good idea

    // Variance-based LB  - lbp::OLBP
    lbp::VARLBP(temp, lbp, radius, neighbours);
    
    // now to show the patterns a normalization is necessary
    // a simple min-max norm will do the job...
    normalize(lbp, lbp, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    uint8_t* pixelPtr = (uint8_t*)lbp.data;
    int cn = lbp.channels();
    for(int i = 0; i < lbp.rows; i++){
        for(int j = 0; j < lbp.cols; j += cn){
            cv::Scalar_<uint8_t> bgrPixel;
            bgrPixel.val[0] = pixelPtr[i*lbp.cols*cn + j*cn + 0];
            
            if (bgrPixel.val[0] < 255 && bgrPixel.val[0] > 5)
                pixelPtr[i*lbp.cols*cn + j*cn + 0] = 255;
            else
                pixelPtr[i*lbp.cols*cn + j*cn + 0] = 0;
        }
    }
    
    cv::Mat cleanedImg;
    cleanedImg = lbp.clone();
    
    std::vector<std::vector<cv::Point> > cnt;
    std::vector<cv::Vec4i> hrch;
    
    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::morphologyEx( cleanedImg, cleanedImg, cv::MORPH_CLOSE, structuringElement );
    
    // Find contours
    findContours( cleanedImg, cnt, hrch, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1 );

    // Get the moments
    std::vector<cv::Moments> mu(cnt.size() );
    for( size_t i = 0; i < cnt.size(); i++ )
        mu[i] = moments( cnt[i], false );
    
    // Get the mass centers:
    std::vector<cv::Point2f> mc( cnt.size() );
    
    for( size_t i = 0; i < cnt.size(); i++ )
        mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
    
    std::vector<std::vector<cv::Point> > contours_poly( cnt.size() );
    std::vector<cv::Rect> boundRect( cnt.size() );
    
    for( size_t i = 0; i< cnt.size(); i++ ){
        
        double length = arcLength( cnt[i], true );
        if ( (mc[i].y > topBound) && (length > minArcLength) && (length < maxArcLength)){
            //yDebug(" Contour[%d] -X[%lf]  -Y[%lf] -Length: %.2f minArc %d maxArc %d topBound %d\n", i, mc[i].x, mc[i].y, length, minArcLength, maxArcLength, topBound );
            //cv::drawContours( extracted, cnt, i, cvScalar(255,255,255), 2, 8, hrch, 0, cv::Point() );

            approxPolyDP( cv::Mat(cnt[i]), contours_poly[i], 3, true );
            boundRect[i] = boundingRect( cv::Mat(contours_poly[i]) );
            
            /*yarp::os::Bottle &t=b.addList();
            t.addDouble(boundRect[i].tl().x);
            t.addDouble(boundRect[i].tl().y);
            t.addDouble(boundRect[i].br().x);
            t.addDouble(boundRect[i].br().y);*/

            double topLeftX = boundRect[i].tl().x;
            double topLeftY = boundRect[i].tl().y;
            double bottomRightX = boundRect[i].br().x;
            double bottomRightY = boundRect[i].br().y;
            
            int shift = 3;
            
            if (topLeftX > shift)
                topLeftX -= shift;
            
            if (topLeftY > shift)
                topLeftY -= shift;
            
            if (bottomRightX > 0 && bottomRightX < (img.width() - shift))
                bottomRightX += shift;
            
            if (bottomRightY > 0 && bottomRightY < (img.height() - shift))
                bottomRightY += shift;
            
            /*-------------------------grabcut on bounding box---------------------------------*/
            
            int blobWidth = std::abs(bottomRightX - topLeftX);
            int blobHeight = std::abs(bottomRightY - topLeftY);
            
            //yDebug("ROI: %d %d %d %d arcLength %.2f \n", boundRect[i].tl().x, boundRect[i].tl().y, blobWidth, blobHeight, length);
            
            cv::Rect roi(boundRect[i].tl().x, boundRect[i].tl().y, blobWidth, blobHeight);

            if (blobWidth > 20 && blobHeight > 20){     //keep it safe for the grabCut algorithm

                //cvtColor( imgMat, imgMat, CV_BGR2RGB);
                cv::Mat image_roi(imgMat, roi);
                
                int border = 3;
                cv::Rect rect;
                rect = cv::Rect( border, border, image_roi.cols - (border*2), image_roi.rows-(border*2));
                
                cv::Mat result; // segmentation result (4 possible values)
                cv::Mat bgModel,fgModel; // the models (internally used)
                
                // GrabCut segmentation
                cv::grabCut(image_roi, result, rect, bgModel, fgModel, numIteration, cv::GC_INIT_WITH_RECT);
                
                // Get the pixels marked as likely foreground
                cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
                
                // Generate output image
                cv::Mat foreground(image_roi.size(),CV_8UC3,cv::Scalar(0,0,0));
                image_roi.copyTo(foreground,result); // bg pixels not copied
                
                ////combine it all for the streaming image
                foreground.copyTo(segmented(cv::Rect(boundRect[i].tl().x, boundRect[i].tl().y, foreground.cols, foreground.rows)));
            }
        }
    }
    
    std::vector<std::vector<cv::Point> > objcnt;
    std::vector<cv::Vec4i> objhrch;
    cv::Mat prov;
    cvtColor(segmented, prov, CV_BGR2GRAY);
    findContours( prov, objcnt, objhrch, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );
    
    // Get the moments
    std::vector<cv::Moments> muSeg(objcnt.size() );
    for( size_t i = 0; i < objcnt.size(); i++ )
        muSeg[i] = moments( objcnt[i], false );
    
    // Get the mass centers:
    std::vector<cv::Point2f> mcSeg( objcnt.size() );
    
    for( size_t i = 0; i < objcnt.size(); i++ )
        mcSeg[i] = cv::Point2f( muSeg[i].m10/muSeg[i].m00 , muSeg[i].m01/muSeg[i].m00 );
    
    std::vector<std::vector<cv::Point> > contours_polySeg( objcnt.size() );
    std::vector<cv::Rect> boundRectSeg( objcnt.size() );
    
    for( size_t i = 0; i< objcnt.size(); i++ ){
        
        cv::drawContours( extracted, objcnt, i, cvScalar(255,255,255), 2, 8, objhrch, 0, cv::Point() );
        
        approxPolyDP( cv::Mat(objcnt[i]), contours_polySeg[i], 3, true );
        boundRectSeg[i] = boundingRect( cv::Mat(contours_polySeg[i]) );
        
        yarp::os::Bottle &t=b.addList();
        t.addDouble(boundRectSeg[i].tl().x);
        t.addDouble(boundRectSeg[i].tl().y);
        t.addDouble(boundRectSeg[i].br().x);
        t.addDouble(boundRectSeg[i].br().y);
        
    }
    
    semComp.unlock();
    
    if (b.size())
        outTargetPort.write();
    
    IplImage propag = imgMat;
    outOrig.resize(propag.width, propag.height);
    cvCopyImage( &propag, (IplImage *) outOrig.getIplImage());
    outPortPropagate.setEnvelope(ts);
    outPortPropagate.write();

    IplImage processed = extracted;//contour
    outImg.resize(processed.width, processed.height);
    cvCopyImage( &processed, (IplImage *) outImg.getIplImage());
    outPortBlobs.setEnvelope(ts);
    outPortBlobs.write();
    
    IplImage seg = segmented;//contour
    outSeg.resize(seg.width, seg.height);
    cvCopyImage( &seg, (IplImage *) outSeg.getIplImage());
    outPortSegmented.setEnvelope(ts);
    outPortSegmented.write();
    
    cv::Mat olbp, tmp;
    cvtColor(imgMat, tmp, CV_BGR2GRAY);
    lbp::OLBP(tmp, olbp); // use the original operator
    normalize(olbp, olbp, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    IplImage orig = lbp;//cleaned local binary pattern
    outLbpContour.resize(orig.width, orig.height);
    cvCopyImage( &orig, (IplImage *) outLbpContour.getIplImage());
    outPortLbpContours.setEnvelope(ts);
    outPortLbpContours.write();
    
    IplImage imag = olbp; // full local binary pattern
    outLbp.resize(imag.width, imag.height);
    cvCopyImage( &imag, (IplImage *) outLbp.getIplImage());
    outPortLbp.setEnvelope(ts);
    outPortLbp.write();

}
//empty line to make gcc happy
