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

/// filtering the image by using sobel method also include magnitudeimage and nonmaximumsuppressionimage
void sobelFilter(const		Mat input,						///< input image
							Mat sobelFilterImageX,			///< sobelFilterImageX
							Mat	sobelFilterImageY,			///< sobelFilterImageY
							Mat magnitudeSobelImage,		///< magnitudeSobelImage
							Mat nonMaximumSuppressionImage)	///< nonMaximumSuppressionImage
{
	const int width		= input.cols;
	const int height	= input.rows;

	Mat sobelX			= Mat::zeros(3, 3, CV_32F);
	Mat sobelY			= Mat::zeros(3, 3, CV_32F);
	Mat paddingIMageX	= Mat::zeros(height + 2, width + 2, CV_8U);
	Mat paddingIMageY	= Mat::zeros(height + 2, width + 2, CV_8U);
	Mat gradientDegree	= Mat::zeros(height, width, CV_32F);

	sobelX.at<float>(0, 0)	= -1.f;
	sobelX.at<float>(0, 1)	= 0.f;
	sobelX.at<float>(0, 2)	= 1.f;
	sobelX.at<float>(1, 0)	= -2.f;
	sobelX.at<float>(1, 1)	= 0.f;
	sobelX.at<float>(1, 2)	= 2.f;
	sobelX.at<float>(2, 0)	= -1.f;
	sobelX.at<float>(2, 1)	= 0.f;
	sobelX.at<float>(2, 2)	= 1.f;

	sobelY.at<float>(0, 0)	= 1.f;
	sobelY.at<float>(0, 1)	= 2.f;
	sobelY.at<float>(0, 2)	= 1.f;
	sobelY.at<float>(1, 0)	= 0.f;
	sobelY.at<float>(1, 1)	= 0.f;
	sobelY.at<float>(1, 2)	= 0.f;
	sobelY.at<float>(2, 0)	= -1.f;
	sobelY.at<float>(2, 1)	= -2.f;
	sobelY.at<float>(2, 2)	= -1.f;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			paddingIMageY.at<uchar>(y + 1, x + 1) = input.at<uchar>(y, x);
		}
	}

	paddingIMageY.convertTo(paddingIMageY, CV_32F);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float filterValue = 0.f;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					filterValue += paddingIMageY.at<float>(y + i, x + j) * sobelY.at<float>(i, j);
				}
			}
			sobelFilterImageY.at<float>(y, x) = filterValue;
		}
	}

	sobelFilterImageY += 127;
	sobelFilterImageY.convertTo(sobelFilterImageY, CV_8U);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			paddingIMageX.at<uchar>(y + 1, x + 1) = input.at<uchar>(y, x);
		}
	}

	paddingIMageX.convertTo(paddingIMageX, CV_32F);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float filterValue = 0.f;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					filterValue += paddingIMageX.at<float>(y + i, x + j) * sobelX.at<float>(i, j);
				}
			}
			sobelFilterImageX.at<float>(y, x) = filterValue;
		}
	}

	sobelFilterImageX += 127;
	sobelFilterImageX.convertTo(sobelFilterImageX, CV_8U);

	sobelFilterImageX -= 127;
	sobelFilterImageY -= 127;

	for (int y = 0; y < height;  y++) {
		for (int x = 0; x < width; x++) {
			magnitudeSobelImage.at<uchar>(y, x) = sqrt(pow(sobelFilterImageX.at<uchar>(y, x), 2) + pow(sobelFilterImageY.at<uchar>(y, x), 2));
		}
	}

	Mat window	= Mat::zeros(3, 3, CV_8U);
	for (int y = 0; y < height - 2; y++) {
		int middle = 0;
		for (int x = 0; x < width - 2; x++) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					window.at<uchar>(i, j) = magnitudeSobelImage.at<uchar>(y + i, x + j);
				}
			}
			middle = window.at<uchar>(1, 1);

			if(middle < window.at<uchar>(0,0)	|| 
				middle < window.at<uchar>(0,1)	|| 
				middle < window.at<uchar>(0,2)	|| 
				middle < window.at<uchar>(1,0)	|| 
				middle < window.at<uchar>(1,2)	||
				middle < window.at<uchar>(2,0)	|| 
				middle < window.at<uchar>(2,1)	|| 
				middle < window.at<uchar>(2,2))
			{
				nonMaximumSuppressionImage.at<uchar>(y + 1,x + 1) = 0;
			} else {
				nonMaximumSuppressionImage.at<uchar>(y + 1,x + 1) = middle;
			}
		}
	}
}

/// filtering the image by using roberts method
void robertsFilter(const	Mat input,					///< inputImage
							Mat robertsFilterImageX,	///< robertsFilterImageX
							Mat robertsFilterImageY)	///< robertsFilterImageY
{
	const int width		= input.cols;
	const int height	= input.rows;

	Mat robertsX	= Mat::zeros(2, 2, CV_32F);
	Mat robertsY	= Mat::zeros(2, 2, CV_32F);

	robertsX.at<float>(0, 0)	= 0;
	robertsX.at<float>(0, 1)	= 1;
	robertsX.at<float>(1, 0)	= -1;
	robertsX.at<float>(1, 1)	= 0;

	robertsY.at<float>(0, 0)	= 1;
	robertsY.at<float>(0, 1)	= 0;
	robertsY.at<float>(1, 0)	= 0;
	robertsY.at<float>(1, 1)	= -1;

	for (int y = 0; y < height - 1; y++) {
		for (int x = 0; x < width - 1; x++) {
			float filterValue = 0.f;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					filterValue += input.at<uchar>(y + i, x + j) * robertsY.at<float>(i, j);
				}
			}
			robertsFilterImageY.at<float>(y, x) = filterValue;
		}
	}

	robertsFilterImageY += 127;
	robertsFilterImageY.convertTo(robertsFilterImageY, CV_8U);

	for (int y = 0; y < height - 1; y++) {
		for (int x = 0; x < width - 1; x++) {
			float	filterValue = 0.f;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					filterValue += input.at<uchar>(y + i, x + j) * robertsX.at<float>(i, j);
				}
			}
			robertsFilterImageX.at<float>(y, x) = filterValue;
		}
	}

	robertsFilterImageX += 127;
	robertsFilterImageX.convertTo(robertsFilterImageX, CV_8U);
}