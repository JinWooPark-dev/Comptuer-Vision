/**
	@mainpage   Computer Vison Assignment
	@brief      Lukas-Kanade Optical Flow headerfile

	@section    detail Detailed Description
	@details    include Lukas-Kanade Optical Flow.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-31
*/

#ifndef opticalFlow_H
#define opticalFlow_H

#include "header.h"

void lukasKanadeOpticalFlow(Mat beforeImage,	///<beforeImage
							Mat	afterImage,		///<afterImage
							Mat &outputImage);	///<outputImage
#endif