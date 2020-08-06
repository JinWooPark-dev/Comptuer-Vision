/**
	@mainpage   Computer Vison Assignment
	@brief      Hough Transform headerfile

	@section    detail Detailed Description
	@details    include Line Detection using Hough Transform.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-06
*/


#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include "header.h"

/// line detection using houghTransfrom method
void lineDetectionUsingHoughTransform(	const	Mat	inputImage,				///< inputImage
												Mat	&lineImage,				///< lineDetectionImage
												int	threshold,				///< threshold Value 
												int	houghSpacethetaSize,	///< houghspace thetasize
												int	houghSpaceRadianSize);	///< houghspace radiansize
#endif
