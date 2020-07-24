/**
	@mainpage   Computer Vison Assignment
	@brief      Corner Image

	@section    detail Detailed Description
	@details    This program is to test corner image.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-24
*/

#include "corner.h"

void harrisCornerDetection(const	Mat input,			///< inputImage
									Mat cornerImage)	///< cornerImage
{
	const	int	width	= input.cols;
	const	int	height	= input.rows;

	Mat sobelX			= Mat::zeros(3, 3, CV_32F); 
	Mat sobelY			= Mat::zeros(3, 3, CV_32F);

	Mat	paddingImageX	= Mat::zeros(height + 2, width + 2, CV_8U);	
	Mat	paddingImageY	= Mat::zeros(height + 2, width + 2, CV_8U);	

	Mat sobelGradientX	= Mat::zeros(height, width, CV_32F);
	Mat sobelGradientY	= Mat::zeros(height, width, CV_32F);

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
			paddingImageY.at<uchar>(y + 1, x + 1)	= input.at<uchar>(y, x);
			paddingImageX.at<uchar>(y + 1, x + 1)	= input.at<uchar>(y, x);
		}
	}

	paddingImageY.convertTo(paddingImageY, CV_32F);
	paddingImageX.convertTo(paddingImageX, CV_32F);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			float	filtervalueY	= 0.f;
			float	filtervalueX	= 0.f;

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					filtervalueY	+= paddingImageY.at<float>(y + i, x + j) * sobelY.at<float>(i, j);
					filtervalueX	+= paddingImageX.at<float>(y + i, x + j) * sobelX.at<float>(i, j);

				}
			}
			sobelGradientY.at<float>(y, x)	= filtervalueY;
			sobelGradientX.at<float>(y, x)	= filtervalueX;
		}
	}

	sobelGradientY.convertTo(sobelGradientY, CV_8U);
	sobelGradientX.convertTo(sobelGradientX, CV_8U);
	
	sobelGradientX -= 127;
	sobelGradientY -= 127;
	
	sobelGradientY.convertTo(sobelGradientY, CV_32F);
	sobelGradientX.convertTo(sobelGradientX, CV_32F);

	vector<vector<Mat>>	secondMomentMatrix(height, vector<Mat>(width));

	for (int y = 0; y < height - 2; y++) {
		for (int x = 0; x < width - 2; x++) {
			secondMomentMatrix[y][x]	= Mat::zeros(2, 2, CV_32F); 
		}
	}

	for (int y = 0; y < height - 2; y++) {
		for (int x = 0; x < width - 2; x++) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					secondMomentMatrix[y][x].at<float>(0, 0)	+= pow(sobelGradientX.at<float>(y + i, x + j), 2);
					secondMomentMatrix[y][x].at<float>(0, 1)	+= sobelGradientX.at<float>(y + i, x + j) * sobelGradientY.at<float>(y + i, x + j);
					secondMomentMatrix[y][x].at<float>(1, 0)	+= sobelGradientX.at<float>(y + i, x + j) * sobelGradientY.at<float>(y + i, x + j);
					secondMomentMatrix[y][x].at<float>(1, 1)	+= pow(sobelGradientY.at<float>(y + i, x + j), 2);
				}
			}
		}
	}

	Mat	harrisCorner	= Mat::zeros(height, width, CV_32F);	
	for (int y = 0; y < height - 2; y++) {
		for (int x = 0; x < width - 2; x++) {
			
			float	detM	= secondMomentMatrix[y][x].at<float>(0, 0) * secondMomentMatrix[y][x].at<float>(1, 1) - secondMomentMatrix[y][x].at<float>(0, 1) * secondMomentMatrix[y][x].at<float>(1, 0);
			float	traceM	= secondMomentMatrix[y][x].at<float>(0, 0) + secondMomentMatrix[y][x].at<float>(1, 1);
			float	R		= detM - 0.04 * pow(traceM, 2);

			if (R > 0)	{
				harrisCorner.at<float>(y, x)	= 255;
			} else{}
		}
	}

	Mat	window	= Mat::zeros(3, 3, CV_32F);  
	for (int y = 0; y < height - 2; y++) {
			int middle	= 0;
		for (int x = 0; x < width - 2; x++) {							
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					window.at<float>(i, j)	= harrisCorner.at<float>(y + i, x + j);
				}
			}

			middle	= window.at<float>(1,1);

			if(middle < window.at<float>(0,0)	|| 
				middle < window.at<float>(0,1)	|| 
				middle < window.at<float>(0,2)	|| 
				middle < window.at<float>(1,0)	|| 
				middle < window.at<float>(1,2)	||
				middle < window.at<float>(2,0)	|| 
				middle < window.at<float>(2,1)	|| 
				middle < window.at<float>(2,2)) {
				harrisCorner.at<float>(y + 1,x + 1) = 0;
			}
			else {
				harrisCorner.at<float>(y + 1,x + 1) = middle;
			}
		}
	}

	cornerImage	= input.clone();

	for (int y = 0; y < height - 2; y++) {
		for (int x = 0; x < width - 2; x++) {
			if (harrisCorner.at<float>(y, x) > 0) {
				circle(cornerImage, Point(x, y), 3, Scalar(255, 255, 255), 2, 8);
			} else{}
		}
	}
	
	//imwrite("E:\\project\\ComputerVision\\outputImage\\harrisCornerImage.png", cornerImage);
}
