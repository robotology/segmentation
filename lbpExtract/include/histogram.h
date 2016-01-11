#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_

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

#include <opencv2/opencv.hpp>
#include <limits>

namespace lbp {

// templated functions
template <typename _Tp>
    void histogram_(const cv::Mat& src, cv::Mat& hist, int numPatterns);

template <typename _Tp>
double chi_square_(const cv::Mat& histogram0, const cv::Mat& histogram1);

// non-templated functions
void spatial_histogram(const cv::Mat& src, cv::Mat& spatialhist, int numPatterns, const cv::Size& window, int overlap=0);

// wrapper functions
void spatial_histogram(const cv::Mat& src, cv::Mat& spatialhist, int numPatterns, int gridx=8, int gridy=8, int overlap=0);
void histogram(const cv::Mat& src, cv::Mat& hist, int numPatterns);
double chi_square(const cv::Mat& histogram0, const cv::Mat& histogram1);

// Mat return type functions
cv::Mat histogram(const cv::Mat& src, int numPatterns);
cv::Mat spatial_histogram(const cv::Mat& src, int numPatterns, const cv::Size& window, int overlap=0);
cv::Mat spatial_histogram(const cv::Mat& src, int numPatterns, int gridx=8, int gridy=8, int overlap=0);
}
#endif
