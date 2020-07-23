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
#include "edge.h"

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

	/* 5. salt and papper noise image
	Mat saltPapperNoiseImage = Mat::zeros(height, width, CV_8U);
	saltPepperNoise(inputImage, saltPapperNoiseImage, 0.1);
	//imwrite("E:\\project\\ComputerVision\\outputImage\\sharpImage.png", saltPapperNoiseImage);	
	/**/

	/* 6. Gaussian noise image
	Mat gaussianNoiseImage = Mat::zeros(height, width, CV_8U);
	gaussianNoise(inputImage, gaussianNoiseImage);
	imwrite("E:\\project\\ComputerVision\\outputImage\\gaussianNoiseImage.png", gaussianNoiseImage);
	/**/
	/* 7. medianFilter image
	Mat medianFilterImage = Mat::zeros(height, width, CV_8U);
	medianFiltering(inputImage, medianFilterImage, 5, 5);
	imwrite("E:\\project\\ComputerVision\\outputImage\\medianFilterImage.png", medianFilterImage);
	/**/

	//Edge filter
	/* 1. prewittFilter image
	Mat prewittFilterImageX = Mat::zeros(height, width, CV_32F);
	Mat prewittFilterImageY = Mat::zeros(height, width, CV_32F);

	prewittFilter(inputImage, prewittFilterImageX, prewittFilterImageY);

	imwrite("E:\\project\\ComputerVision\\outputImage\\prewittFilterImageX.png", prewittFilterImageX);
	imwrite("E:\\project\\ComputerVision\\outputImage\\prewittFilterImageY.png", prewittFilterImageY);
	/**/

	// 2. sobelFilter image
	Mat	sobelFilterImageX			= Mat::zeros(height, width, CV_32F);
	Mat	sobelFilterImageY			= Mat::zeros(height, width, CV_32F);
	Mat	magnitudeSobelImage			= Mat::zeros(height, width, CV_8U);
	Mat	nonMaximumSuppressionImage	= Mat::zeros(height, width, CV_8U);

	sobelFilter(inputImage, sobelFilterImageX, sobelFilterImageY, magnitudeSobelImage, nonMaximumSuppressionImage);	

	//imwrite("E:\\project\\ComputerVision\\outputImage\\sobelFilterImageX.png", sobelFilterImageX);
	//imwrite("E:\\project\\ComputerVision\\outputImage\\sobelFilterImageY.png", sobelFilterImageY);
	//imwrite("E:\\project\\ComputerVision\\outputImage\\magnitudeSobelImage.png", magnitudeSobelImage);
	//imwrite("E:\\project\\ComputerVision\\outputImage\\nonMaximumSuppressionImage.png", nonMaximumSuppressionImage);
	/**/

	/* 3. robertesFiltering
	Mat	robertsFilterImageX	= Mat::zeros(height, width, CV_32F);
	Mat	robertsFilterImageY	= Mat::zeros(height, width, CV_32F);

	robertsFilter(inputImage, robertsFilterImageX, robertsFilterImageY);

	imwrite("E:\\project\\ComputerVision\\outputImage\\robertsFilterImageX.png", robertsFilterImageX);
	imwrite("E:\\project\\ComputerVision\\outputImage\\robertsFilterImageY.png", robertsFilterImageY);
	/**/

	Mat	highThreshold	= Mat::zeros(height, width, CV_8U);
	Mat	lowThreshold	= Mat::zeros(height, width, CV_8U);

	hysteresisThreshold(nonMaximumSuppressionImage, highThreshold, lowThreshold);

	//imwrite("E:\\project\\ComputerVision\\outputImage\\highThreshold.png", highThreshold);
	//imwrite("E:\\project\\ComputerVision\\outputImage\\lowThreshold.png", lowThreshold);

	Mat	cannyEdgeImage	= Mat::zeros(height, width, CV_8U);
	edgeLinking(highThreshold, lowThreshold, cannyEdgeImage);

	imwrite("E:\\project\\ComputerVision\\outputImage\\cannyEdgeImage.png", cannyEdgeImage);

	return 0;
}