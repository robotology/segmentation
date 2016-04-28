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

#include <cstdio>
#include "dispBlobber.hpp"

using namespace std;

dispBlobber::dispBlobber(int imH, int imW, int _bufferSize,
        int _margin,
        int _backgroundThresh,
        int _minBlobSize, int _gaussSize,
        int _imageThreshRatioLow, int _imageThreshRatioHigh)
{

    aux.create(imH, imW, CV_8U);
    fillMask.create(imH + 2, imW + 2, CV_8U);

    margin = _margin;
    
    backgroundThresh = _backgroundThresh;       // threshold of intensity on the image under which info is ignored
    
    minBlobSize = _minBlobSize;
    
    gaussSize = _gaussSize;

    imageThreshRatioLow = _imageThreshRatioLow;
    imageThreshRatioHigh = _imageThreshRatioHigh;
    
    blue = cv::Scalar(255,0,0);
    green = cv::Scalar(0,255,0);
    red = cv::Scalar(0,0,255);
    white = cv::Scalar(255,255,255);

    bufferSize = _bufferSize;

}

bool dispBlobber::setThresh(int low)
{
    if ( low<0 || low>255 ) {
        fprintf(stdout,"Please select valid luminance values (0-255). \n");
        return false;
    }

    fprintf(stdout,"New Threshold is : %i\n", low);
    backgroundThresh = low;
    return true;
}

bool dispBlobber::setMargin(int mrg)
{
    fprintf(stdout,"New margin : %d\n", mrg);
    margin = mrg;
    return true;
}

double dispBlobber::extractBlob(std::vector<cv::Mat> &images, std::vector<int> &roi, std::vector<int> &centroid, cv::Mat &blob)
{

    cv::Mat image = images[0].clone();

    cv::cvtColor(image, image, CV_BGR2GRAY);


    /* Filter */

    double sigmaX1 = 1.5;
    double sigmaY1 = 1.5;
    cv::GaussianBlur(image, image, cv::Size(gaussSize,gaussSize), sigmaX1, sigmaY1);

    cv::threshold(image, image, backgroundThresh, -1, CV_THRESH_TOZERO);

    int dilate_niter = 4;
    int erode_niter = 2;
    double sigmaX2 = 2;
    double sigmaY2 = 2;
    
    cv::dilate(image, image, cv::Mat(), cv::Point(-1,-1), dilate_niter, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());

    cv::GaussianBlur(image, image, cv::Size(gaussSize,gaussSize), sigmaX2, sigmaY2, cv::BORDER_DEFAULT);

    cv::erode(image, image, cv::Mat(), cv::Point(-1,-1), erode_niter, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());


    /* Find closest valid blob */
    
    double minVal, maxVal; 
    cv::Point minLoc, maxLoc;

    int fillFlags = 8 | ( 255 << 8 ) | cv::FLOODFILL_FIXED_RANGE; // flags for floodFill
    
    aux = image.clone();

    int fillSize = 0;
    while (fillSize < minBlobSize){         

        cv::minMaxLoc( aux, &minVal, &maxVal, &minLoc, &maxLoc );

        // if its too small, paint it black and search again
        fillSize = floodFill(aux, maxLoc, 0, 0, cv::Scalar(maxVal/imageThreshRatioLow), cv::Scalar(maxVal/imageThreshRatioHigh), fillFlags);

    }
    // paint closest valid blob white
    fillMask.setTo(0);
    cv::floodFill(image, fillMask, maxLoc, 255, 0, cv::Scalar(maxVal/imageThreshRatioLow), cv::Scalar(maxVal/imageThreshRatioHigh), cv::FLOODFILL_MASK_ONLY + fillFlags);

    /* Find contours */

    std::vector<std::vector<cv::Point > > contours;
    std::vector<cv::Vec4i> hierarchy;

    // use aux because findContours modify the input image
    aux = fillMask(cv::Range(1,image.rows+1), cv::Range(1,image.cols+1)).clone();
    cv::findContours( aux, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );


    /* If any blob is found check again that only the biggest valid blob is selected */
        
    int blobI = -1;
    double blobSizeOld = -1, blobSize = -1;
    for( size_t c = 0; c < contours.size(); c++ ){
        
        // find the area of contour
        blobSize = cv::contourArea(contours[c]);

        // select only the biggest valid blob
        if( blobSize > minBlobSize && blobSize > blobSizeOld)
        {
            blobI = c;
            blobSizeOld = blobSize;
        }
    }
        
    /* If any blob is found (after the double-check) */

    if (blobI>=0)
    {

        /* Get the ROI */

        cv::Rect blobBox = cv::boundingRect(contours[blobI]);

        cv::Rect imBox(cv::Point(std::max(blobBox.tl().x-margin,0),std::max(blobBox.tl().y-margin,0)),cv::Point(std::min(blobBox.br().x+margin,image.cols-1),std::min(blobBox.br().y+margin,image.rows-1)));


        /* Get the current centroid */

        cv::Moments mu = moments( contours[blobI], false );

        //cv::Point center2Dcoords = cv::Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );
        cv::Point2f center2Dcoords = cv::Point2f( mu.m10/mu.m00 , mu.m01/mu.m00 );

        /* Update the buffer */

        center2DcoordsBuffer.push_back(center2Dcoords);

        if ((int)center2DcoordsBuffer.size()>bufferSize) {
            assert(!center2DcoordsBuffer.empty());
            center2DcoordsBuffer.erase(center2DcoordsBuffer.begin());
        }

        /* Update the mean */

        cv::Point2f zero(0.0f, 0.0f);
        cv::Point2f sum  = std::accumulate(center2DcoordsBuffer.begin(), center2DcoordsBuffer.end(), zero);
        mean_centroid.x = (int)round(sum.x / center2DcoordsBuffer.size());
        mean_centroid.y = (int)round(sum.y / center2DcoordsBuffer.size());

        /* Return results */

        roi.push_back(imBox.tl().x);
        roi.push_back(imBox.tl().y);

        roi.push_back(imBox.br().x);
        roi.push_back(imBox.br().y);

        //centroid.push_back(center2Dcoords.x);
        //centroid.push_back(center2Dcoords.y);
        centroid.push_back(mean_centroid.x);
        centroid.push_back(mean_centroid.y);

        fillMask(cv::Range(1,image.rows+1), cv::Range(1,image.cols+1)).copyTo(blob);

    }
    else
    {

        blob = cv::Mat::zeros(image.rows, image.cols, CV_8U);

        blobSize = -1;

        centroid.push_back(mean_centroid.x);
        centroid.push_back(mean_centroid.y);
    }
    
    return blobSize;
}

