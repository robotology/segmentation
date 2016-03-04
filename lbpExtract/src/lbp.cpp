
//! Original code by philipp <bytefish[at]gmx[dot]de>
//! \copyright BSD, see LICENSE.

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

#include <cmath>
#include "lbp.h"

/************************************************************************/
template <typename _Tp>
void lbp::OLBP_(const cv::Mat& src, cv::Mat& dst) {
    
    dst = cv::Mat::zeros(src.rows-2, src.cols-2, CV_8UC1);
    for(int i=1;i<src.rows-1;i++) {
        for(int j=1;j<src.cols-1;j++) {
            _Tp center = src.at<_Tp>(i,j);
            unsigned char code = 0;
            code |= (src.at<_Tp>(i-1,j-1) > center) << 7;
            code |= (src.at<_Tp>(i-1,j) > center) << 6;
            code |= (src.at<_Tp>(i-1,j+1) > center) << 5;
            code |= (src.at<_Tp>(i,j+1) > center) << 4;
            code |= (src.at<_Tp>(i+1,j+1) > center) << 3;
            code |= (src.at<_Tp>(i+1,j) > center) << 2;
            code |= (src.at<_Tp>(i+1,j-1) > center) << 1;
            code |= (src.at<_Tp>(i,j-1) > center) << 0;
            dst.at<unsigned char>(i-1,j-1) = code;
        }
    }
}

/************************************************************************/
template <typename _Tp>
void lbp::ELBP_(const cv::Mat& src, cv::Mat& dst, int radius, int neighbors) {
    neighbors = std::max(std::min(neighbors,31),1); // set bounds...
    dst = cv::Mat::zeros(src.rows-2*radius, src.cols-2*radius, CV_32SC1);
    
    for(int n=0; n<neighbors; n++) {
        // sample points
        float x = static_cast<float>(radius) * cos(2.0*M_PI*n/static_cast<float>(neighbors));
        float y = static_cast<float>(radius) * -sin(2.0*M_PI*n/static_cast<float>(neighbors));
        // relative indices
        int fx = static_cast<int>(floor(x));
        int fy = static_cast<int>(floor(y));
        int cx = static_cast<int>(ceil(x));
        int cy = static_cast<int>(ceil(y));
        // fractional part
        float ty = y - fy;
        float tx = x - fx;
        // set interpolation weights
        float w1 = (1 - tx) * (1 - ty);
        float w2 =      tx  * (1 - ty);
        float w3 = (1 - tx) *      ty;
        float w4 =      tx  *      ty;
        // iterate through your data
        for(int i=radius; i < src.rows-radius;i++) {
            for(int j=radius;j < src.cols-radius;j++) {
                float t = w1*src.at<_Tp>(i+fy,j+fx) + w2*src.at<_Tp>(i+fy,j+cx) + w3*src.at<_Tp>(i+cy,j+fx) + w4*src.at<_Tp>(i+cy,j+cx);
                // we are dealing with floating point precision, so add some little tolerance
                dst.at<unsigned int>(i-radius,j-radius) += ((t > src.at<_Tp>(i,j)) && (std::abs(t-src.at<_Tp>(i,j)) > (int)std::numeric_limits<float>::epsilon())) << n;
            }
        }
    }
}

/************************************************************************/
template <typename _Tp>
void lbp::VARLBP_(const cv::Mat& src, cv::Mat& dst, int radius, int neighbors) {
    
    std::max(std::min(neighbors,31),1); // set bounds
    dst = cv::Mat::zeros(src.rows-2*radius, src.cols-2*radius, CV_32FC1); //! result
    // allocate some memory for temporary on-line variance calculations
    cv::Mat _mean = cv::Mat::zeros(src.rows, src.cols, CV_32FC1);
    cv::Mat _delta = cv::Mat::zeros(src.rows, src.cols, CV_32FC1);
    cv::Mat _m2 = cv::Mat::zeros(src.rows, src.cols, CV_32FC1);
    for(int n=0; n<neighbors; n++) {
        // sample points
        float x = static_cast<float>(radius) * cos(2.0*M_PI*n/static_cast<float>(neighbors));
        float y = static_cast<float>(radius) * -sin(2.0*M_PI*n/static_cast<float>(neighbors));
        // relative indices
        int fx = static_cast<int>(floor(x));
        int fy = static_cast<int>(floor(y));
        int cx = static_cast<int>(ceil(x));
        int cy = static_cast<int>(ceil(y));
        // fractional part
        float ty = y - fy;
        float tx = x - fx;
        // set interpolation weights
        float w1 = (1 - tx) * (1 - ty);
        float w2 =      tx  * (1 - ty);
        float w3 = (1 - tx) *      ty;
        float w4 =      tx  *      ty;
        // iterate through your data
        for(int i=radius; i < src.rows-radius;i++) {
            for(int j=radius;j < src.cols-radius;j++) {
                float t = w1*src.at<_Tp>(i+fy,j+fx) + w2*src.at<_Tp>(i+fy,j+cx) + w3*src.at<_Tp>(i+cy,j+fx) + w4*src.at<_Tp>(i+cy,j+cx);
                _delta.at<float>(i,j) = t - _mean.at<float>(i,j);
                _mean.at<float>(i,j) = (_mean.at<float>(i,j) + (_delta.at<float>(i,j) / (1.0*(n+1)))); // i am a bit paranoid
                _m2.at<float>(i,j) = _m2.at<float>(i,j) + _delta.at<float>(i,j) * (t - _mean.at<float>(i,j));
            }
        }
    }
    // calculate result
    for(int i = radius; i < src.rows-radius; i++) {
        for(int j = radius; j < src.cols-radius; j++) {
            dst.at<float>(i-radius, j-radius) = _m2.at<float>(i,j) / (1.0*(neighbors-1));
        }
    }
}

/************************************************************************/
// now the wrapper functions
void lbp::OLBP(const cv::Mat& src, cv::Mat& dst){
    switch(src.type()) {
        case CV_8SC1: OLBP_<char>(src, dst); break;
        case CV_8UC1: OLBP_<unsigned char>(src, dst); break;
        case CV_16SC1: OLBP_<short>(src, dst); break;
        case CV_16UC1: OLBP_<unsigned short>(src, dst); break;
        case CV_32SC1: OLBP_<int>(src, dst); break;
        case CV_32FC1: OLBP_<float>(src, dst); break;
        case CV_64FC1: OLBP_<double>(src, dst); break;
    }
}

/************************************************************************/
void lbp::ELBP(const cv::Mat& src, cv::Mat& dst, int radius, int neighbors){
    switch(src.type()) {
        case CV_8SC1: ELBP_<char>(src, dst, radius, neighbors); break;
        case CV_8UC1: ELBP_<unsigned char>(src, dst, radius, neighbors); break;
        case CV_16SC1: ELBP_<short>(src, dst, radius, neighbors); break;
        case CV_16UC1: ELBP_<unsigned short>(src, dst, radius, neighbors); break;
        case CV_32SC1: ELBP_<int>(src, dst, radius, neighbors); break;
        case CV_32FC1: ELBP_<float>(src, dst, radius, neighbors); break;
        case CV_64FC1: ELBP_<double>(src, dst, radius, neighbors); break;
    }
}

/************************************************************************/
void lbp::VARLBP(const cv::Mat& src, cv::Mat& dst, int radius, int neighbors){
    switch(src.type()) {
        case CV_8SC1: VARLBP_<char>(src, dst, radius, neighbors); break;
        case CV_8UC1: VARLBP_<unsigned char>(src, dst, radius, neighbors); break;
        case CV_16SC1: VARLBP_<short>(src, dst, radius, neighbors); break;
        case CV_16UC1: VARLBP_<unsigned short>(src, dst, radius, neighbors); break;
        case CV_32SC1: VARLBP_<int>(src, dst, radius, neighbors); break;
        case CV_32FC1: VARLBP_<float>(src, dst, radius, neighbors); break;
        case CV_64FC1: VARLBP_<double>(src, dst, radius, neighbors); break;
    }
}

/************************************************************************/
// now the Mat return functions
cv::Mat lbp::OLBP(const cv::Mat& src){
    cv::Mat dst;
    OLBP(src, dst);
    return dst;
}

/************************************************************************/
cv::Mat lbp::ELBP(const cv::Mat& src, int radius, int neighbors){
    cv::Mat dst;
    ELBP(src, dst, radius, neighbors);
    return dst;
}

/************************************************************************/
cv::Mat lbp::VARLBP(const cv::Mat& src, int radius, int neighbors) {
    cv::Mat dst;
    VARLBP(src, dst, radius, neighbors);
    return dst;
}




