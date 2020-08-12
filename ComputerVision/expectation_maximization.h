/**
	@mainpage   Computer Vison Assignment
	@brief      Expectation and Maximization headerfile

	@section    detail Detailed Description
	@details    include expectation and maximization.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-12
*/

/// stereo matching using ssd(sum of squared difference)
#ifndef EXPECTATION_MAXIMIZATION_H
#define EXPECTATION_MAXIMIZATION_H

#include "header.h"

void expectationMaximization	(	const	Mat clock,					///< clock image
									const	Mat clockPaint,				///< clockPaint image
											Mat	&binarySegmentation,	///< disparityMap
									const	int nRepetition);			///< number of repetition
#endif