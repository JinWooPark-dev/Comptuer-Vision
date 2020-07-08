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