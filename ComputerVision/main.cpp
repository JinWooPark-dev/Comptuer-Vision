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
#include "corner.h"
#include "clustering.h"
#include "opticalFlow.h"
#include "fitting.h"
#include "houghTransform.h"

int main()
{
	/*
	Mat inputImage = imread("E:\\project\\ComputerVision\\inputImage\\son.jpg", 0);

	int width	= inputImage.cols;
	int height	= inputImage.rows;
	/**/

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

	/* 2. sobelFilter image
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

	/* 4. hysteresis threshold
	Mat	highThreshold	= Mat::zeros(height, width, CV_8U);
	Mat	lowThreshold	= Mat::zeros(height, width, CV_8U);

	hysteresisThreshold(nonMaximumSuppressionImage, highThreshold, lowThreshold);

	imwrite("E:\\project\\ComputerVision\\outputImage\\highThreshold.png", highThreshold);
	imwrite("E:\\project\\ComputerVision\\outputImage\\lowThreshold.png", lowThreshold);
	/**/

	/* 5. canny edge image
	Mat	cannyEdgeImage	= Mat::zeros(height, width, CV_8U);
	edgeLinking(highThreshold, lowThreshold, cannyEdgeImage);

	imwrite("E:\\project\\ComputerVision\\outputImage\\cannyEdgeImage.png", cannyEdgeImage);
	/**/
	
	/* 1. Corner detection
	//Harris corner detection
	Mat	harrisCornerImage	= Mat::zeros(height, width, CV_32F);

	harrisCornerDetection(inputImage, harrisCornerImage);
	/**/

	/* Clustering
	enum{NUM_POINT  = 100};
	enum{NUM_GROUP  = 3};

	const   int height      = 500;
	const   int width       = 1000;

	vector<Point2f>	point(NUM_GROUP * NUM_POINT);
	Mat draw    = Mat::zeros(height, width, CV_8UC3);
	Mat outputImage    = Mat::zeros(height, width, CV_8UC3);

	vector<Point>   center(NUM_GROUP);
	center[0]   = Point(200, 100);
	center[1]   = Point(400, 350);
	center[2]   = Point(700, 200);
	const   float   sigma   = 50;

	RNG rng;
	for (int i = 0; i < NUM_GROUP; i++) {
		for (int j = 0; j < NUM_POINT; j++) {
			point[i * NUM_POINT + j]    = Point2f(center[i].x + rng.gaussian(sigma), center[i].y + rng.gaussian(sigma));
			circle(draw, point[i * NUM_POINT + j], 2, Scalar(255, 255, 255), 2);
		}
	}

	k_meansClustering(draw, outputImage, point);

	imwrite("E:\\project\\ComputerVision\\outputImage\\clusteringImage.png", outputImage);
	/**/
	
	/*
	Mat	inputImage	= imread("E:\\project\\ComputerVision\\inputImage\\native.jpg", 1);

	int	width	= inputImage.cols;
	int	height	= inputImage.rows;

	Mat	outputImage	= Mat::zeros(height, width, CV_8UC3);
	*/

	/*
	imageSegmentation(inputImage, outputImage, 15);
	imwrite("E:\\project\\ComputerVision\\outputImage\\imageSegmentation.png", outputImage);
	*/

	/*
	imageSegmentationUsingColorSpace_Location(inputImage, outputImage, 15);
	imwrite("E:\\project\\ComputerVision\\outputImage\\imageSegmentationUsingColorSpace.png", outputImage);
	*/
	
	/*
	imageSegmentationUsingMeanShift(inputImage, outputImage);
	imwrite("E:\\project\\ComputerVision\\outputImage\\imageSegmentationUsingMeanShift.png", outputImage);
	*/

	/*
	Mat	beforeImage	= imread("E:\\project\\ComputerVision\\inputImage\\yosemite0.png", 0);
	Mat	afterImage	= imread("E:\\project\\ComputerVision\\inputImage\\yosemite1.png", 0);
	
	const	int	width	= beforeImage.cols;
	const	int	height	= beforeImage.rows;

	Mat outputImage	= Mat::zeros(height, width, CV_8UC3);

	lukasKanadeOpticalFlow(beforeImage, afterImage, outputImage);
	*/

	/*
		line fitting
	enum{NUM_POINT  = 100};
	const   int     height      = 500;
	const   int     width       = 1000;
	const   int     marginSize  = 200;
	const   Point2f margin      = Point2f(float(marginSize), float(marginSize));

	vector<Point2f> point(NUM_POINT);
	Mat graph   = Mat::zeros(height + 2 * marginSize, width + 2 * marginSize, CV_8UC3);

	const   float   mean    = 5.f;
	const   float   sigma   = 5.f;
	const   float   slope   = 0.5f;
	const   float   bias    = 50.f;

	RNG rng;
	for (int i = 0; i < NUM_POINT; i++) {
		point[i]    = Point2f(float(10 * i), slope * (10 * i) + bias) + Point2f(mean * rng.gaussian(sigma), mean * rng.gaussian(sigma));
		circle(graph, point[i] + margin, 2, Scalar(255, 255, 255), 2);
	}


	vector<Point2f> noisePoint(2 * NUM_POINT);
	Mat noiseGraph  = Mat::zeros(height + 2 * marginSize, width + 2 * marginSize, CV_8UC3);

	const   float   largeSigma  = 10 * sigma;
	for (int i = 0; i < NUM_POINT; i++) {
		noisePoint[i]               = point[i];
		noisePoint[i + NUM_POINT]   = Point2f(10 * i, slope * (10 * i) + bias) + Point2f(mean * rng.gaussian(largeSigma), mean * rng.gaussian(largeSigma));
	}

	for (int i = 0; i < 2 * NUM_POINT; i++) {
		circle(noiseGraph, noisePoint[i] + margin, 2, Scalar(255, 255, 255), 2);
	}

	Mat	outputImage	= graph.clone();
	*/
	/*
		lineFitting (graph, outputImage, point, 100, margin);	
		imwrite("E:\\project\\ComputerVision\\outputImage\\lineFitting.png", outputImage);
	*/

	/*
	lineFittingUsingRansac (noiseGraph,	outputImage, noisePoint, margin);

	imwrite("E:\\project\\ComputerVision\\outputImage\\lineFittingUsingRansac.png", outputImage);
	*/

	/* houghTransform
	*/

	Mat inputImage = imread("E:\\project\\ComputerVision\\inputImage\\check.png", 0);

	int	width	= inputImage.cols;
	int	height	= inputImage.rows;

	Mat	lineImage	= Mat::zeros(height, width, CV_8UC3);

	lineDetectionUsingHoughTransform(inputImage, lineImage, 170, 1500, 180);

	imwrite("E:\\project\\ComputerVision\\outputImage\\lineDetectionUsingHoughTransform.png", lineImage);

	return 0;
}