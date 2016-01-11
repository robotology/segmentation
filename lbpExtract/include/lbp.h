#ifndef LBP_HPP_
#define LBP_HPP_

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
void OLBP_(const cv::Mat& src, cv::Mat& dst);

template <typename _Tp>
void ELBP_(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);

template <typename _Tp>
void VARLBP_(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);

// wrapper functions
void OLBP(const cv::Mat& src, cv::Mat& dst);
void ELBP(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);
void VARLBP(const cv::Mat& src, cv::Mat& dst, int radius = 1, int neighbors = 8);

// Mat return type functions
cv::Mat OLBP(const cv::Mat& src);
cv::Mat ELBP(const cv::Mat& src, int radius = 1, int neighbors = 8);
cv::Mat VARLBP(const cv::Mat& src, int radius = 1, int neighbors = 8);

}
#endif
