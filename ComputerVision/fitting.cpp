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

/// liineFitting using ransac method
void lineFittingUsingRansac (	const	Mat				inputImage,		///< inputImage
										Mat				&outputImage,	///< outputImage
										vector<Point2f>	point,			///< circle point
										Point			margin)			///< size of margin
{
	const	int	width	= inputImage.cols;
	const	int	height	= inputImage.rows;
	
	int		distanceCountMax	= 0;
	float	gradient			= 0.f;
	float	interceptY			= 0.f;
	
	vector<int>		randomValue(2);
	vector<float>	fittingLine(2);
	for (int i = 0; i < 50; i++) {
		randomValue[0]	= (int)(rand() % 200);
		randomValue[1]	= (int)(rand() % 200);
		gradient		= (point[randomValue[0]].y - point[randomValue[1]].y) / (point[randomValue[0]].x - point[randomValue[1]].x);
		interceptY		= point[randomValue[0]].y - gradient * point[randomValue[0]].x;
		int	distanceCount	= 0;
		for (int j = 0; j < 200; j++) {
			float	distance	= abs(gradient * point[j].x - point[j].y + interceptY) / sqrt( pow(gradient, 2) + 1);
			if (distance < 20) {
				distanceCount++;
			} else{}
		}
		if (distanceCount > distanceCountMax) {
			fittingLine[0]		= gradient;
			fittingLine[1]		= interceptY;
			distanceCountMax	= distanceCount;
		} else{}
	}
	float	minX	= point[0].x;
	float	maxX	= point[0].x;
	for (int i = 0; i < 200; i++) {
		if (minX > point[i].x) {
			minX	= point[i].x;
		} else if (maxX < point[i].x) {
			maxX	= point[i].x;
		} else{}
	}
	line(outputImage, Point(int(minX), int(minX * fittingLine[0] + fittingLine[1])) + margin, Point(int(maxX), int(maxX * fittingLine[0] + fittingLine[1])) + margin, Scalar(0, 0, 255));
}