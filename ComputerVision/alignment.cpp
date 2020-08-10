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


/// topview image using homography method
void homographyTransform(	const	Mat inputImage,				///< before homography transform image
									Mat referenceSquareImage,	///< referenceSquare image
									Mat	topViewImage)			///< topView Image
{
	const	int	width	= inputImage.cols;
	const	int	height	= inputImage.rows;

	vector<Point2f>	krakowPoint(4);
	krakowPoint[0]	= Point2f(600, 1004);
	krakowPoint[1]	= Point2f(769, 945);
	krakowPoint[2]	= Point2f(876, 1022);
	krakowPoint[3]	= Point2f(697, 1091);

	vector<Point2f>	paperPoint(4);
	paperPoint[0]	= Point2f(233, 596);
	paperPoint[1]	= Point2f(325, 596);
	paperPoint[2]	= Point2f(325, 674);
	paperPoint[3]	= Point2f(233, 674);

	Mat	paper			= Mat::zeros(8, 8, CV_32F);
	Mat	paperTranspos	= Mat::zeros(8, 8, CV_32F);
	
	paper.at<float>(0, 0)	= paperPoint[0].x;
	paper.at<float>(0, 1)	= paperPoint[0].y;
	paper.at<float>(0, 2)	= 1.f;
	paper.at<float>(0, 6)	= -1.f * paperPoint[0].x * krakowPoint[0].x;
	paper.at<float>(0, 7)	= -1.f * paperPoint[0].y * krakowPoint[0].x;
	
	paper.at<float>(1, 3)	= paperPoint[0].x;
	paper.at<float>(1, 4)	= paperPoint[0].y;
	paper.at<float>(1, 5)	= 1.f;
	paper.at<float>(1, 6)	= -1.f * paperPoint[0].x * krakowPoint[0].y;
	paper.at<float>(1, 7)	= -1.f * paperPoint[0].y * krakowPoint[0].y;
	
	paper.at<float>(2, 0)	= paperPoint[1].x;
	paper.at<float>(2, 1)	= paperPoint[1].y;
	paper.at<float>(2, 2)	= 1.f;
	paper.at<float>(2, 6)	= -1.f * paperPoint[1].x * krakowPoint[1].x;
	paper.at<float>(2, 7)	= -1.f * paperPoint[1].y * krakowPoint[1].x;
	
	paper.at<float>(3, 3)	= paperPoint[1].x;
	paper.at<float>(3, 4)	= paperPoint[1].y;
	paper.at<float>(3, 5)	= 1.f;
	paper.at<float>(3, 6)	= -1.f * paperPoint[1].x * krakowPoint[1].y;
	paper.at<float>(3, 7)	= -1.f * paperPoint[1].y * krakowPoint[1].y;
	
	paper.at<float>(4, 0)	= paperPoint[2].x;
	paper.at<float>(4, 1)	= paperPoint[2].y;
	paper.at<float>(4, 2)	= 1.f;
	paper.at<float>(4, 6)	= -1.f * paperPoint[2].x * krakowPoint[2].x;
	paper.at<float>(4, 7)	= -1.f * paperPoint[2].y * krakowPoint[2].x;
	
	paper.at<float>(5, 3)	= paperPoint[2].x;
	paper.at<float>(5, 4)	= paperPoint[2].y;
	paper.at<float>(5, 5)	= 1.f;
	paper.at<float>(5, 6)	= -1.f * paperPoint[2].x * krakowPoint[2].y;
 	paper.at<float>(5, 7)	= -1.f * paperPoint[2].y * krakowPoint[2].y;
	
	paper.at<float>(6, 0)	= paperPoint[3].x;
	paper.at<float>(6, 1)	= paperPoint[3].y;
	paper.at<float>(6, 2)	= 1.f;
	paper.at<float>(6, 6)	= -1.f * paperPoint[3].x * krakowPoint[3].x;
	paper.at<float>(6, 7)	= -1.f * paperPoint[3].y * krakowPoint[3].x;
	
	paper.at<float>(7, 3)	= paperPoint[3].x;
	paper.at<float>(7, 4)	= paperPoint[3].y;
	paper.at<float>(7, 5)	= 1.f;
	paper.at<float>(7, 6)	= -1.f * paperPoint[3].x * krakowPoint[3].y;
	paper.at<float>(7, 7)	= -1.f * paperPoint[3].y * krakowPoint[3].y;

	Mat	parameter	= Mat::zeros(8, 1, CV_32F);
	Mat	krakow		= Mat::zeros(8, 1, CV_32F);

	krakow.at<float>(0, 0)	= krakowPoint[0].x;
	krakow.at<float>(1, 0)	= krakowPoint[0].y;
	krakow.at<float>(2, 0)	= krakowPoint[1].x;
	krakow.at<float>(3, 0)	= krakowPoint[1].y;
	krakow.at<float>(4, 0)	= krakowPoint[2].x;
	krakow.at<float>(5, 0)	= krakowPoint[2].y;
	krakow.at<float>(6, 0)	= krakowPoint[3].x;
	krakow.at<float>(7, 0)	= krakowPoint[3].y;

	transpose(paper, paperTranspos);
	Mat	inverse	= paperTranspos * paper;
	parameter	= inverse.inv() * paperTranspos * krakow;

	vector<Mat>	chanelInputImage(3);
	split(inputImage, chanelInputImage);

	//Mat outImage	= Mat::zeros(height, width, CV_8UC3);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float	paperX			= parameter.at<float>(0, 0) * x + parameter.at<float>(1, 0) * y + parameter.at<float>(2, 0);
			float	paperY			= parameter.at<float>(3, 0) * x + parameter.at<float>(4, 0) * y + parameter.at<float>(5, 0);
			float	homographyValue	= parameter.at<float>(6, 0) * x + parameter.at<float>(7, 0) * y + 1.f;
			paperX	/=	homographyValue;
			paperY	/=	homographyValue;
			if (paperX >= 0 && paperX <= width && paperY >= 0 && paperY <= height) {
				topViewImage.at<Vec3b>(y, x)[0]	= chanelInputImage[0].at<uchar>(paperY, paperX);
				topViewImage.at<Vec3b>(y, x)[1]	= chanelInputImage[1].at<uchar>(paperY, paperX);
				topViewImage.at<Vec3b>(y, x)[2]	= chanelInputImage[2].at<uchar>(paperY, paperX);
			} else{}
		}
	}
}