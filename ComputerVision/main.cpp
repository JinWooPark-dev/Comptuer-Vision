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
	Mat inputImage = imread("E:\\project\\ComputerVision\\inputImage\\son.jpg", 0);

	int width	= inputImage.cols;
	int height	= inputImage.rows;

	//Image_Filtering
	/* 1. boxFilter
	Mat boxFilterImage = Mat::zeros(height, width, CV_8U);
	boxFiltering(inputImage, boxFilterImage, 11, 11);	
	imwrite("E:\\project\\ComputerVision\\outputImage\\boxFilterImage.png", boxFilterImage);
	/**/

	/* 2. Gaussian Filter
	Mat gaussianImage = Mat::zeros(height, width, CV_8U);
	gaussianFiltering(inputImage, gaussianImage, 11, 11);
	imwrite("E:\\project\\ComputerVision\\outputImage\\gaussianImage.png", gaussianImage);	
	/**/

	/* 3. Seprable Kernel
	Mat separableKernelImage = Mat::zeros(height, width, CV_8U);
	separableKernel(inputImage, separableKernelImage, 11, 11);
	imwrite("E:\\project\\ComputerVision\\outputImage\\separableKernelImage.png", separableKernelImage);	
	/**/

	/* 4. Sharpeing image
	Mat sharpImage	= Mat::zeros(height, width, CV_8U);
	imageSharpening(inputImage, sharpImage, 11, 11);
	imwrite("E:\\project\\ComputerVision\\outputImage\\sharpImage.png", sharpImage);	
	/**/

	Mat saltPapperNoiseImage = Mat::zeros(height, width, CV_8U);
	saltPepperNoise(inputImage, saltPapperNoiseImage, 0.1);
	imwrite("E:\\project\\ComputerVision\\outputImage\\sharpImage.png", saltPapperNoiseImage);	
	
	return 0;
}