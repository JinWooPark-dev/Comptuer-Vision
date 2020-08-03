/**
	@mainpage   Computer Vison Assignment
	@brief      line fitting 

	@section    detail Detailed Description
	@details    include Line fitting using least square method and ransan method.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-03
*/

#include "fitting.h"


/// liineFitting using least square method
void lineFitting (	const	Mat				inputImage,		///< inputImage
							Mat				&outputImage,	///< outputImage
							vector<Point2f>	point,			///< circle point
							int				numPoint,		///< Num of Point
							Point			margin)			///< size of margin
{
	const	int	width	= inputImage.cols;
	const	int	height	= inputImage.rows;

	Mat	xPoint			= Mat::ones(numPoint, 2, CV_32F);
	Mat	xPointTrans		= Mat::zeros(2, numPoint, CV_32F);
	Mat	lineValue		= Mat::zeros(2, 1, CV_32F);
	Mat	yPoint			= Mat::ones(numPoint, 2, CV_32F);

	float	minX		= point[0].x;
	float	maxX		= point[0].x;

	for (int i = 0; i < numPoint; i++) {
		xPoint.at<float>(i, 0)	= point[i].x;
		yPoint.at<float>(i, 0)	= point[i].y;
		if (minX > point[i].x && point[i].x > 0) {
			minX	= point[i].x;
		} else if (maxX < point[i].x) {
			maxX	= point[i].x;
		} else{}
	}
	transpose(xPoint, xPointTrans);
	Mat	inverse	= xPointTrans * xPoint;
	lineValue	= inverse.inv() * xPointTrans * yPoint; 
	
	cout<<"lineValue : "<<lineValue.at<float>(0,0) <<" : "<<lineValue.at<float>(1,0)<<endl;
	line(outputImage, Point(int(minX), int(minX * lineValue.at<float>(0,0) + lineValue.at<float>(1,0))) + margin, Point(int(maxX), int(maxX * lineValue.at<float>(0,0) + lineValue.at<float>(1,0))) + margin, Scalar(0, 0, 255));
}
