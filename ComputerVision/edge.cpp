/**
	@mainpage   Computer Vison Assignment
	@brief      Edge Image

	@section    detail Detailed Description
	@details    This program is to test edge image.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-15
*/

#include "edge.h"

/// filtering the image by using prewitt method
void prewittFilter(const	Mat input,					///< inputImage
							Mat prewittFilterImageX,	///< prewittFilterImageX
							Mat prewittFilterImageY)	///< prewittFilterImageY
{
	const	int width	= input.cols;
	const	int height	= input.rows;

	Mat prewittX		= Mat::zeros(3, 3, CV_32F);
	Mat prewittY		= Mat::zeros(3, 3, CV_32F);
	Mat paddingImageX	= Mat::zeros(height + 2, width + 2, CV_8U);
	Mat paddingImageY	= Mat::zeros(height + 2, width + 2, CV_8U);

	prewittX.at<float>(0, 0)	= -1.f;
	prewittX.at<float>(0, 1)	= 0.f;
	prewittX.at<float>(0, 2)	= 1.f;
	prewittX.at<float>(1, 0)	= -1.f;
	prewittX.at<float>(1, 1)	= 0.f;
	prewittX.at<float>(1, 2)	= 1.f;
	prewittX.at<float>(2, 0)	= -1.f;
	prewittX.at<float>(2, 1)	= 0.f;
	prewittX.at<float>(2, 2)	= 1.f;

	prewittY.at<float>(0, 0)	= 1.f;
	prewittY.at<float>(0, 1)	= 1.f;
	prewittY.at<float>(0, 2)	= 1.f;
	prewittY.at<float>(1, 0)	= 0.f;
	prewittY.at<float>(1, 1)	= 0.f;
	prewittY.at<float>(1, 2)	= 0.f;
	prewittY.at<float>(2, 0)	= -1.f;
	prewittY.at<float>(2, 1)	= -1.f;
	prewittY.at<float>(2, 2)	= -1.f;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			paddingImageY.at<uchar>(y + 1, x + 1) = input.at<uchar>(y, x);
		}
	}

	paddingImageY.convertTo(paddingImageY, CV_32F);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float filterValue = 0.f;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					filterValue += paddingImageY.at<float>(y + i, x + j) * prewittY.at<float>(i, j);
				}
			}
			prewittFilterImageY.at<float>(y, x) = filterValue;
		}
	}

	prewittFilterImageY += 127;
	prewittFilterImageY.convertTo(prewittFilterImageY, CV_8U);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			paddingImageX.at<uchar>(y + 1, x + 1) = input.at<uchar>(y, x);
		}
	}

	paddingImageX.convertTo(paddingImageX, CV_32F);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float filterValue = 0.f;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					filterValue += paddingImageX.at<float>(y + i, x + j) * prewittX.at<float>(i, j);
				}
			}
			prewittFilterImageX.at<float>(y, x) = filterValue;
		}
	}

	prewittFilterImageX += 127;
	prewittFilterImageX.convertTo(prewittFilterImageX, CV_8U);
}