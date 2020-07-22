/**
	@mainpage   Computer Vison Assignment
	@brief      Edge headerfile

	@section    detail Detailed Description
	@details    include Edge function.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-15
*/

#ifndef EDGE_H
#define EDGE_H

#include "header.h"

/// filtering the image by using prewitt method
void prewittFilter(const	Mat input,					///< inputImage
							Mat prewittFilterImageX,	///< prewittFilterImageX
							Mat prewittFilterImageY);	///< prewittFilterImageY

/// filtering the image by using sobel method also include magnitudeimage and nonmaximumsuppressionimage
void sobelFilter(const		Mat input,							///< input image
							Mat sobelFilterImageX,				///< sobelFilterImageX
							Mat	sobelFilterImageY,				///< sobelFilterImageY
							Mat magnitudeSobelImage,			///< magnitudeSobelImage
							Mat nonMaximumSuppressionImage);	///< nonMaximumSuppressionImage

/// filtering the image by using roberts method
void robertsFilter(const	Mat input,					///< inputImage
							Mat robertsFilterImageX,	///< robertsFilterImageX
							Mat robertsFilterImageY);	///< robertsFilterImageY

#endif