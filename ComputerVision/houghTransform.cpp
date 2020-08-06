/**
	@mainpage   Computer Vison Assignment
	@brief      Hough Transform 

	@section    detail Detailed Description
	@details    include Line Detection using Hough Transform.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2017-06-15
*/

#include "houghTransform.h"

/// line detection using houghTransfrom method
void lineDetectionUsingHoughTransform(	const	Mat	inputImage,				///< inputImage
												Mat	&lineImage,				///< lineDetectionImage
												int	threshold,				///< threshold Value 
												int	houghSpacethetaSize,	///< houghspace thetasize
												int	houghSpaceRadianSize)	///< houghspace radiansize
{
	const	int	width	= inputImage.cols;
	const	int	height	= inputImage.rows;

	Mat	cannyImage;
	Mat	houghSpace	= Mat::zeros(houghSpaceRadianSize, houghSpacethetaSize, CV_8U);

	Canny(inputImage, cannyImage, 125, 255);

	vector<vector<int>>	voting(houghSpaceRadianSize);
	for (int i = 0; i < houghSpaceRadianSize; i++) {
		voting[i].resize(houghSpacethetaSize);
	}
	float	min	= 0.f;
	float	max	= 0.f;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (cannyImage.at<uchar>(y, x) == 255) {
				for (float angle = 0; angle < 180; angle++) {					
					float	distance	= x * cos(angle * 3.14/180) + y * sin(angle * 3.14/180);					
					if (min > distance) {
						min	= distance;
					}	else if (max < distance) {
						max	= distance;
					}	else{}
					distance	/= 10.f;
					distance	= floorf(distance);
					if (distance < 0) {
						distance	+=	1.f;
						distance	*= -1.f;
						voting[int(distance)][int(angle)]	+= 1;
					}	else {
						voting[int(distance + 50)][int(angle)]	+= 1;
					}
				} 
			} else{}
		}
	}
	cout<<"min : "<<min<<endl;
	cout<<"max : "<<max<<endl;
	float	votingMaxCount	= 0.f;
	for (int i = 0; i < houghSpaceRadianSize; i++) {
		for (int j = 0; j < houghSpacethetaSize; j++) {
			if (votingMaxCount < voting[i][j]) {
				votingMaxCount	= voting[i][j];
			} else{}
		}
	}
	float	normalizeValue	= 255 / votingMaxCount;
	for (int i = 0; i < houghSpaceRadianSize; i++) {
		for (int j = 0; j < houghSpacethetaSize; j++) {
			houghSpace.at<uchar>(i, j)	= voting[i][j] * normalizeValue;
		}
	}
	imshow("houghSpace", houghSpace);
	waitKey(0);
	for (int r = 0; r < houghSpaceRadianSize; r++) {
		for (int theta = 0; theta < houghSpacethetaSize; theta++) {
			if (houghSpace.at<uchar>(r, theta) > threshold ) {
				int tempTheta	= theta;
				int tempR		= r - 50;
				if (tempR < 0) {
					tempR -= 1;
				}	else{}
				tempR	*= 10;
				line(lineImage, Point(0, int(tempR/ sin(tempTheta * 3.14/180))), Point(width, int((-(cos(tempTheta * 3.14/180) / sin(tempTheta * 3.14/180)) * width) +  (tempR / sin(tempTheta * 3.14/180)))), Scalar(0, 0, 255));
			} else{}
		}
	}
	imshow("lineImage", lineImage);
	waitKey(0);
}