
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

#include <opencv2/core/core_c.h>
#include "histogram.h"
#include <vector>

/************************************************************************/
template <typename _Tp>
void lbp::histogram_(const cv::Mat& src, cv::Mat& hist, int numPatterns) {
    hist = cv::Mat::zeros(1, numPatterns, CV_32SC1);
    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {
            int bin = src.at<_Tp>(i,j);
            hist.at<int>(0,bin) += 1;
        }
    }
}

/************************************************************************/
template <typename _Tp>
double lbp::chi_square_(const cv::Mat& histogram0, const cv::Mat& histogram1) {
    if(histogram0.type() != histogram1.type())
        CV_Error(CV_StsBadArg, "Histograms must be of equal type.");
    if(histogram0.rows != 1 || histogram0.rows != histogram1.rows || histogram0.cols != histogram1.cols)
        CV_Error(CV_StsBadArg, "Histograms must be of equal dimension.");
    double result = 0.0;
    for(int i=0; i < histogram0.cols; i++) {
        double a = histogram0.at<_Tp>(0,i) - histogram1.at<_Tp>(0,i);
        double b = histogram0.at<_Tp>(0,i) + histogram1.at<_Tp>(0,i);
        if(std::abs(b) > std::numeric_limits<double>::epsilon()) {
            result+=(a*a)/b;
        }
    }
    return result;
}

/************************************************************************/
void lbp::spatial_histogram(const cv::Mat& src, cv::Mat& hist, int numPatterns, const cv::Size& window, int overlap) {
    int width = src.cols;
    int height = src.rows;
    std::vector<cv::Mat> histograms;
    for(int x=0; x < width - window.width; x+=(window.width-overlap)) {
        for(int y=0; y < height-window.height; y+=(window.height-overlap)) {
            cv::Mat cell = cv::Mat(src, cv::Rect(x,y,window.width, window.height));
            histograms.push_back(histogram(cell, numPatterns));
        }
    }
    hist.create(1, histograms.size()*numPatterns, CV_32SC1);
    // i know this is a bit lame now... feel free to make this a bit more efficient...
    for(size_t histIdx=0; histIdx < histograms.size(); histIdx++) {
        for(int valIdx = 0; valIdx < numPatterns; valIdx++) {
            int y = histIdx*numPatterns+valIdx;
            hist.at<int>(0,y) = histograms[histIdx].at<int>(valIdx);
        }
    }
}

/************************************************************************/
void lbp::histogram(const cv::Mat& src, cv::Mat& hist, int numPatterns) {
    switch(src.type()) {
        case CV_8SC1: histogram_<char>(src, hist, numPatterns); break;
        case CV_8UC1: histogram_<unsigned char>(src, hist, numPatterns); break;
        case CV_16SC1: histogram_<short>(src, hist, numPatterns); break;
        case CV_16UC1: histogram_<unsigned short>(src, hist, numPatterns); break;
        case CV_32SC1: histogram_<int>(src, hist, numPatterns); break;
    }
}

/************************************************************************/
double lbp::chi_square(const cv::Mat& histogram0, const cv::Mat& histogram1) {
    switch(histogram0.type()) {
        case CV_8SC1: return chi_square_<char>(histogram0,histogram1); break;
        case CV_8UC1: return chi_square_<unsigned char>(histogram0,histogram1); break;
        case CV_16SC1: return chi_square_<short>(histogram0, histogram1); break;
        case CV_16UC1: return chi_square_<unsigned short>(histogram0,histogram1); break;
        case CV_32SC1: return chi_square_<int>(histogram0,histogram1); break;
    }
}

/************************************************************************/
void lbp::spatial_histogram(const cv::Mat& src, cv::Mat& dst, int numPatterns, int gridx, int gridy, int overlap) {
    int width = static_cast<int>(floor(src.cols/gridx));
    int height = static_cast<int>(floor(src.rows / gridy));
    spatial_histogram(src, dst, numPatterns, cv::Size_<int>(width, height), overlap);
}

/************************************************************************/
cv::Mat lbp::histogram(const cv::Mat& src, int numPatterns) {
    cv::Mat hist;
    histogram(src, hist, numPatterns);
    return hist;
}

/************************************************************************/
cv::Mat lbp::spatial_histogram(const cv::Mat& src, int numPatterns, const cv::Size& window, int overlap) {
    cv::Mat hist;
    spatial_histogram(src, hist, numPatterns, window, overlap);
    return hist;
}

/************************************************************************/
cv::Mat lbp::spatial_histogram(const cv::Mat& src, int numPatterns, int gridx, int gridy, int overlap) {
    cv::Mat hist;
    spatial_histogram(src, hist, numPatterns, gridx, gridy);
    return hist;
}
