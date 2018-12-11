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

#ifndef __DISPBLOBBER_H__
#define __DISPBLOBBER_H__

#include <string>
#include <vector>
#include <numeric>

#include <opencv2/opencv.hpp>

class dispBlobber
{
    int margin;

    int backgroundThresh;

    int minBlobSize;
    int maxBlobSize;
    int gaussSize;
    
    int imageThreshRatioLow;
    int imageThreshRatioHigh;
    
    cv::Scalar blue, green, red, white;

    cv::Mat aux, fillMask;

    std::vector<cv::Point2f > center2DcoordsBuffer;
    int bufferSize;

    cv::Point mean_centroid;

public:

    dispBlobber(int imH, int imW, int _bufferSize,
            int _margin,
            int _backgroundThresh,
            int _minBlobSize, int _maxBlobSize, int _gaussSize,
            int _dispThreshRatioLow, int _dispThreshRatioHigh);

    bool setThresh(int low);
    bool setMargin(int mrg);

    double extractBlob(std::vector<cv::Mat> &images, std::vector<int> &roi, std::vector<int> &centroid, cv::Mat &blob);
       
};

#endif
