/**
@mainpage   Computer Vison Assignment
@brief      Lukas-Kanade Optical Flow headerfile

@section    detail Detailed Description
@details    include Lukas-Kanade Optical Flow.

@section    author Author Information
@author     Jinwoo Park
@date       2020-07-31
*/

#include "opticalFlow.h"

void lukasKanadeOpticalFlow(Mat beforeImage,	///<beforeImage
							Mat	afterImage,		///<afterImage
							Mat &outputImage)	///<outputImage
{
	const int width		= beforeImage.cols;
	const int height	= beforeImage.rows;

	Mat sobelX			= Mat::zeros(3, 3, CV_32F); 
	Mat sobelY			= Mat::zeros(3, 3, CV_32F);

	Mat	paddingImage	= Mat::zeros(height + 2, width + 2, CV_8U);	

	Mat sobelGradientX	= Mat::zeros(height, width, CV_32F);
	Mat sobelGradientY	= Mat::zeros(height, width, CV_32F);

	const	int	windowSize	= 25;

	sobelX.at<float>(0, 0)	= -1;
	sobelX.at<float>(0, 1)	= 0;
	sobelX.at<float>(0, 2)	= 1;
	sobelX.at<float>(1, 0)	= -2;
	sobelX.at<float>(1, 1)	= 0;
	sobelX.at<float>(1, 2)	= 2;
	sobelX.at<float>(2, 0)	= -1;
	sobelX.at<float>(2, 1)	= 0;
	sobelX.at<float>(2, 2)	= 1;

	sobelY.at<float>(0, 0)	= 1;
	sobelY.at<float>(0, 1)	= 2;
	sobelY.at<float>(0, 2)	= 1;
	sobelY.at<float>(1, 0)	= 0;
	sobelY.at<float>(1, 1)	= 0;
	sobelY.at<float>(1, 2)	= 0;
	sobelY.at<float>(2, 0)	= -1;
	sobelY.at<float>(2, 1)	= -2;
	sobelY.at<float>(2, 2)	= -1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			paddingImage.at<uchar>(y + 1, x + 1)	= beforeImage.at<uchar>(y, x);
		}
	}

	paddingImage.convertTo(paddingImage, CV_32F);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			float	filtervalueY	= 0.f;
			float	filtervalueX	= 0.f;

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					filtervalueY	+= paddingImage.at<float>(y + i, x + j) * sobelY.at<float>(i, j);
					filtervalueX	+= paddingImage.at<float>(y + i, x + j) * sobelX.at<float>(i, j);
				}
			}
			sobelGradientY.at<float>(y, x)	= filtervalueY;
			sobelGradientX.at<float>(y, x)	= filtervalueX;
		}
	}

	float sumDx		= 0.f;
	float sumDy		= 0.f;
	float sumDxDy	= 0.f;
	float sumDxDt	= 0.f;
	float sumDyDt	= 0.f;

	Mat dt		= Mat::zeros(windowSize, windowSize, CV_32F);
	Mat inverse	= Mat::zeros(2, 2, CV_32F);

	vector<vector<Point2f>>	opticalFlow(height);
	for (int i = 0; i < height; i++) {
		opticalFlow[i].resize(width);
	}

	int	halfSize	= floor(windowSize / 2.f);

	for (int y = halfSize; y < height - halfSize; y++) {
		for (int x = halfSize; x < width - halfSize; x++) {

			sumDx	= 0.f;
			sumDxDy	= 0.f;
			sumDy	= 0.f;
			sumDxDt	= 0.f;
			sumDyDt	= 0.f;

			for (int i = -halfSize; i < halfSize; i++) {
				for (int j = -halfSize; j < halfSize; j++) {
					sumDx	+= pow(sobelGradientX.at<float>(y + i, x + j), 2);
					sumDxDy	+= sobelGradientX.at<float>(y + i, x + j) * sobelGradientY.at<float>(y + i, x + j);
					sumDy	+= pow(sobelGradientY.at<float>(y + i, x + j), 2);

					dt.at<float>(i + halfSize, j + halfSize)	= int(afterImage.at<uchar>(y + i, x + j)) - int(beforeImage.at<uchar>(y + i, x + j));
					sumDxDt += sobelGradientX.at<float>(y + i, x + j) * dt.at<float>(i + halfSize, j + halfSize);
					sumDyDt += sobelGradientY.at<float>(y + i, x + j) * dt.at<float>(i + halfSize, j + halfSize);
				}
			}

			Mat	tmp		= Mat::zeros(2, 2, CV_32F);
			Mat	tmp2	= Mat::zeros(2, 1, CV_32F);

			tmp.at<float>(0, 0)	= sumDx;
			tmp.at<float>(0, 1)	= sumDxDy;
			tmp.at<float>(1, 0)	= sumDxDy;
			tmp.at<float>(1, 1)	= sumDy;

			tmp2.at<float>(0, 0)	= -sumDxDt;
			tmp2.at<float>(1, 0)	= -sumDyDt;

			Mat	inverse	= tmp.inv();
			Mat	mul		= inverse * tmp2;

			opticalFlow[y][x].x	= mul.at<float>(0, 0);
			opticalFlow[y][x].y	= mul.at<float>(1, 0);
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float	angle	= (atan2( (opticalFlow[y][x].y) , (opticalFlow[y][x].x) ) * 180.f) / PI;
			float	magnitude	= sqrt(opticalFlow[y][x].x * opticalFlow[y][x].x + opticalFlow[y][x].y * opticalFlow[y][x].y);
			
			if (angle < 0) {
				angle += 360;
			}
			float	scaleFactor	= 40.f;
			if (angle < 120) {
				outputImage.at<Vec3b>(y, x)[0]	= 0;
				outputImage.at<Vec3b>(y, x)[1]	= (magnitude * scaleFactor * angle) > 255 ? 255 : magnitude * scaleFactor * angle;
				outputImage.at<Vec3b>(y, x)[2]	= (magnitude * scaleFactor * (120 - angle)) > 255 ? 255 : magnitude * scaleFactor * (120 - angle);	
			} else if (angle < 240) {
				angle	-= 120;
				outputImage.at<Vec3b>(y, x)[0]	= (magnitude * scaleFactor * angle) > 255 ? 255 : magnitude * scaleFactor * angle;		
				outputImage.at<Vec3b>(y, x)[1]	= (magnitude * scaleFactor * (120 - angle)) > 255 ? 255 : magnitude * scaleFactor * (120 - angle);
				outputImage.at<Vec3b>(y, x)[2]	= 0;								
			} else {
				angle	-= 240;
				outputImage.at<Vec3b>(y, x)[0]	= (magnitude * scaleFactor * (120 - angle)) > 255 ? 255 : magnitude * scaleFactor * (120 - angle);	
				outputImage.at<Vec3b>(y, x)[1]	= 0;								// G
				outputImage.at<Vec3b>(y, x)[2]	= (magnitude * scaleFactor * angle) > 255 ? 255 : magnitude * scaleFactor * angle;
			}
		}
	}
	imshow("outputImage", outputImage);
	waitKey(0);
}





















