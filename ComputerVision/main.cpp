/**
	@mainpage	Computer Vison
	@brief		main function

	@section	detail Detailed Description
	@details	This program is about computer vision.

	@section	author Author Information
	@author		Jinwoo Park
	@date		2020-07-04
*/
#include "image_filtering.h"

int main()
{
	Mat inputImage = imread("E:\\project\\ComputerVision\\inputImage\\001.jpg", 0);

	int width	= inputImage.cols;
	int height	= inputImage.rows;

	//Image_Filtering
	Mat boxFilterImage = Mat::zeros(height, width, CV_8U);
	boxFiltering(inputImage, boxFilterImage, 11, 11);
	
	imwrite("E:\\project\\ComputerVision\\outputImage\\boxFilterImage.png", boxFilterImage);

	return 0;
}