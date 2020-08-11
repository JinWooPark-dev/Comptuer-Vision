/**
	@mainpage   Computer Vison Assignment
	@brief      Stereo Matching headerfile

	@section    detail Detailed Description
	@details    include Stereo Matching.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-11
*/

/// stereo matching using ssd(sum of squared difference)
#ifndef STEREO_MATCHING_H
#define STEREO_MATCHING_H

#include "header.h"

void windowMatching	(	const	Mat leftImage,		///< leftImage
						const	Mat rightImage,		///< rightImage
								Mat	&disparityMap,	///< disparityMap
						const	int	windowSize,		///< windowsize
						const	int maxDisparity);	///< max Disparity
#endif