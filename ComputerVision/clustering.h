/*
	@mainpage   Computer Vison Assignment
	@brief      Clustering and Segmentation headerfile

	@section    detail Detailed Description
	@details    include k-means clustering and image segmentation using k-means and mean-shift.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-25
*/

#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "header.h"

inline double	SQR(double	value)
{
	return	value * value;
}

void k_meansClustering (const	Mat inputImage,			///< inputImage
								Mat &outputImage,		///< outputImage
								vector<Point2f> point);	///< circle Point 

void imageSegmentation(const	Mat inputImage,		///< inputImage
								Mat &outputImage,	///< outputImage
								int kValue);			///< kvalue

void imageSegmentationUsingColorSpace_Location(const	Mat inputImage,		///< inputImage
														Mat &outputImage,	///< outputImage
														int kValue);		///< k value

void imageSegmentationUsingMeanShift(const	Mat inputImage,		///<inputImage
											Mat &outputImage);	///<outputImage
#endif