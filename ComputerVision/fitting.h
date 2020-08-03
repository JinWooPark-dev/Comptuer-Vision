/**
	@mainpage   Computer Vison Assignment
	@brief      Line Fitting headerfile

	@section    detail Detailed Description
	@details    include Line fitting using least square method and ransan method.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-03
*/

#ifndef FITTING_H
#define FITTING_H

#include "header.h"

/// liineFitting using least square method
void lineFitting (	const	Mat				inputImage,		///< inputImage
							Mat				&outputImage,	///< outputImage
							vector<Point2f>	point,			///< circle point
							int				numPoint,		///< Num of Point
							Point			margin);			///< size of margin
#endif
