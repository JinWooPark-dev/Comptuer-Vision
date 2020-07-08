/**
	@mainpage	Computer Vison
	@brief		main function

	@section	detail Detailed Description
	@details	This program is about computer vision.

	@section	author Author Information
	@author		Jinwoo Park
	@date		2020-07-04
*/
#include <iostream>
#include "opencv.hpp"
#include "core/core.hpp"
#include "highgui/highgui.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat test = imread("E:\\project\\ComputerVision\\inputImage\\001.jpg", 1);

	imshow("test", test);
	waitKey(0);
	

	return 0;
}