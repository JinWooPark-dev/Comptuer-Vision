/**
	@mainpage   Computer Vison Assignment
	@brief      Alignment headerfile

	@section    detail Detailed Description
	@details    include Alignment.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-09
*/


#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include "header.h"

/// image transform using afine transform
void afiineTransform(	const	Mat	inputImage,		///< before affine transform image
								Mat	&outputImage);	///< after affine transform image
#endif