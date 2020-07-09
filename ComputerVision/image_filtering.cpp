/**
	@mainpage   Computer Vison Assignment
	@brief      Image Filtering

	@section    detail Detailed Description
	@details    This program is to test image filtering.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-09
*/

#include "image_filtering.h"

/// filtering the image using box methond
void boxFiltering(const Mat input,			///< inputImage
						Mat output,			///< outputImage
						int filterSizeX,	///< filterSizeX
						int filterSizeY)	///< filterSizeY
{
	int width	= input.cols;
	int height	= input.rows;

	Mat boxFilter	= Mat::ones(filterSizeX, filterSizeY, CV_32F);
	boxFilter	/= filterSizeX * filterSizeY;

	for (int y = 0; y < height - (filterSizeY - 1); y++) {
		for (int x = 0; x < width - (filterSizeX - 1); x++) {
			float filt	= 0.f;

			for (int i = 0; i < filterSizeX; i++) {
				for (int j = 0; j <filterSizeY; j++) {
					filt += input.at<uchar>(y + i, x + j) * boxFilter.at<float>(i, j);
				}
			}
			output.at<uchar>(y, x) = filt;
		}
	}

}

/// filtering the image using gaussian methond
void gaussianFiltering(const	Mat input,			///< inputImage
								Mat output,			///< outputImage
								int filterSizeX,	///< filterSizeX
								int filterSizeY)	///< filterSizeY
{
	int width	= input.cols;
	int height	= input.rows;

	float sigma	= 5.f;

	Mat gaussian		= Mat::zeros(filterSizeY, filterSizeX, CV_32F);
	Mat paddingImage	= Mat::zeros(height + (filterSizeY - 1), width + (filterSizeX - 1), CV_8U);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			paddingImage.at<uchar>(y + (filterSizeY - 1)/2, x + (filterSizeX - 1)/2) = input.at<uchar>(y, x);
		}
	}

	float	sumGaussian = 0.f;

	for (int y = -(filterSizeY/2); y <= (filterSizeY/2); y++) {
		for (int x = -(filterSizeX/2); x <= (filterSizeX/2); x++) {
			float exponeentialComponent	= (pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2));
			gaussian.at<float>(y + filterSizeY/2, x + filterSizeX/2) = (1 / (2 * PI * pow(sigma, 2))) * exp(-1.f * exponeentialComponent);
			sumGaussian += gaussian.at<float>(y + filterSizeY/2, x + filterSizeX/2);
		}
	}

	gaussian /= sumGaussian;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float filterValue = 0.f;

			for (int i = 0; i < filterSizeX; i++) {
				for (int j = 0; j < filterSizeY; j++) {
					filterValue += paddingImage.at<uchar>(y + i, x + i) * gaussian.at<float>(i, j);
				}
			}

			output.at<uchar>(y, x) = filterValue;
		}
	}

}
