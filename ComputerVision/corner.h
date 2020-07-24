/**
	@mainpage   Computer Vison Assignment
	@brief      Corner headerfile

	@section    detail Detailed Description
	@details    include Corner function.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-24
*/

#ifndef CORNER_H
#define CORNER_H
#include "header.h"

void harrisCornerDetection(const	Mat input,			///< inputImage
									Mat cornerImage);	///< cornerImage
#endif