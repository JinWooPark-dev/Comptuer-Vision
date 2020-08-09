/**
	@mainpage   Computer Vison Assignment
	@brief      Alignment headerfile

	@section    detail Detailed Description
	@details    include Alignment.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-09
*/

#include "alignment.h"

/// image transform using afine transform
void afiineTransform(	const	Mat inputImage,		///< before affine transform image
								Mat &outputImage)	///< after affine transform image
{
	vector<Point2f>	monalisaPoint(4);
	monalisaPoint[0]	= Point2f(51, 50);
	monalisaPoint[1]	= Point2f(232, 50);
	monalisaPoint[2]	= Point2f(232, 325);
	monalisaPoint[3]	= Point2f(51, 325);

	vector<Point2f>	framePoint(4);
	framePoint[0]	= Point2f(440, 123);
	framePoint[1]	= Point2f(772, 242);
	framePoint[2]	= Point2f(616, 677);
	framePoint[3]	= Point2f(284, 557);

	Mat	monalisa			= Mat::zeros(6, 1, CV_32F);
	Mat	frameTransPose		= Mat::zeros(6, 6, CV_32F);
	Mat	parameter			= Mat::zeros(6, 1, CV_32F);
	Mat	frame				= Mat::zeros(6, 6, CV_32F);

	frame.at<float>(0, 0)	= framePoint[0].x;
	frame.at<float>(0, 1)	= framePoint[0].y;
	frame.at<float>(0, 4)	= 1.f;

	frame.at<float>(1, 2)	= framePoint[0].x;
	frame.at<float>(1, 3)	= framePoint[0].y;
	frame.at<float>(1, 5)	= 1.f;

	frame.at<float>(2, 0)	= framePoint[1].x;
	frame.at<float>(2, 1)	= framePoint[1].y;
	frame.at<float>(2, 4)	= 1.f;

	frame.at<float>(3, 2)	= framePoint[1].x;
	frame.at<float>(3, 3)	= framePoint[1].y;
	frame.at<float>(3, 5)	= 1.f;

	frame.at<float>(4, 0)	= framePoint[2].x;
	frame.at<float>(4, 1)	= framePoint[2].y;
	frame.at<float>(4, 4)	= 1.f;

	frame.at<float>(5, 2)	= framePoint[2].x;
	frame.at<float>(5, 3)	= framePoint[2].y;
	frame.at<float>(5, 5)	= 1.f;


	monalisa.at<float>(0, 0)	= monalisaPoint[0].x;
	monalisa.at<float>(1, 0)	= monalisaPoint[0].y;
	monalisa.at<float>(2, 0)	= monalisaPoint[1].x;
	monalisa.at<float>(3, 0)	= monalisaPoint[1].y;
	monalisa.at<float>(4, 0)	= monalisaPoint[2].x;
	monalisa.at<float>(5, 0)	= monalisaPoint[2].y;

	transpose(frame, frameTransPose);
	Mat	inverse	= frameTransPose * frame;
	parameter	= inverse.inv() * frameTransPose * monalisa;

	Mat	gray	= Mat::zeros(outputImage.rows, outputImage.cols, CV_32F);
	cvtColor(outputImage, gray, CV_RGB2GRAY);	 
	vector<Point>	innerFramePoint;
	for (int i = 0; i <= 1380; i = i + 2) {
		for (int j = 440 + -1 * (0.1141 * i); j <= 772 + -1 * (0.1139 * i); j++) {
			float y = -1 * 0.3584 * (j + i) + 34.6848 ;
			if (gray.at<uchar>(-1 * y, j) == 255) {
				innerFramePoint.push_back(Point(j, -1 * y));
			} else{}
			gray.at<uchar>(-1 * y, j)	= 0;
		}	
	}
	vector<Mat>	chanelInputImage(3);
	split(inputImage, chanelInputImage);

	for (int i  = 0; i < innerFramePoint.size(); i++) { 
			float	frameX	= parameter.at<float>(0, 0) * innerFramePoint[i].x + parameter.at<float>(1, 0) * innerFramePoint[i].y + parameter.at<float>(4, 0);
			float	frameY	= parameter.at<float>(2, 0) * innerFramePoint[i].x + parameter.at<float>(3, 0) * innerFramePoint[i].y + parameter.at<float>(5, 0);
			outputImage.at<Vec3b>(innerFramePoint[i].y, innerFramePoint[i].x)[0]	= chanelInputImage[0].at<uchar>(frameY, frameX);
			outputImage.at<Vec3b>(innerFramePoint[i].y, innerFramePoint[i].x)[1]	= chanelInputImage[1].at<uchar>(frameY, frameX);
			outputImage.at<Vec3b>(innerFramePoint[i].y, innerFramePoint[i].x)[2]	= chanelInputImage[2].at<uchar>(frameY, frameX);	
	}
}
