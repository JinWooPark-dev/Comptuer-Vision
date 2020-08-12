/**
@mainpage   Computer Vison Assignment
@brief      Expectation and Maximization sourcefile

@section    detail Detailed Description
@details    include expectation and maximization.

@section    author Author Information
@author     Jinwoo Park
@date       2020-08-12
*/
#include "expectation_maximization.h"

/// Expectation and maximization function
void expectationMaximization	(	const	Mat clock,					///< clock image
									const	Mat clockPaint,				///< clockPaint image
											Mat	&binarySegmentation,	///< disparityMap
									const	int nRepetition)			///< number of repetition
{
	const	int	width	= clock.cols;
	const	int	height	= clock.rows;

	vector<float>	foregroundIntensity;
	vector<float>	backgroundIntensity;

	vector<Mat>	chanelClockPaint(3);
	split(clockPaint, chanelClockPaint);

	for (int repetition = 0; repetition < nRepetition; repetition++) {
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (chanelClockPaint[0].at<uchar>(y, x) == 255) {
					if (repetition == 0) {
						backgroundIntensity.push_back(clock.at<uchar>(y, x));
					} else {
						backgroundIntensity.push_back(binarySegmentation.at<uchar>(y, x));
					}
				} else if (chanelClockPaint[2].at<uchar>(y, x) == 255) {
					if (repetition == 0) {
						foregroundIntensity.push_back(clock.at<uchar>(y, x));
					} else {
						foregroundIntensity.push_back(binarySegmentation.at<uchar>(y, x));
					}
				}
			}
		}
		vector<Point2f>	foregroundDistribution;
		vector<Point2f>	backgroundDistribution;

		float	mean	= 0.f;
		for (int i = 0; i < foregroundIntensity.size(); i++) {
			mean	+= foregroundIntensity[i];
		}
		mean	/= foregroundIntensity.size();
		cout<<"mean : "<<mean<<endl;
		float	sigma	= 0.f;
		for (int i = 0; i < foregroundIntensity.size(); i++) {
			sigma	+= pow(foregroundIntensity[i] - mean, 2);
		}
		sigma	/= foregroundIntensity.size();
		cout<<"sigma : "<<sigma<<endl;
		for (int i = 0; i <= 255; i++) {
			float	value	= (1 / sqrt(2 * PI * sigma)) * exp(-1 * pow(i - mean, 2) / (2 * sigma));
			foregroundDistribution.push_back(Point2f(i, value));	
		}

		mean	= 0.f;
		for (int i = 0; i < backgroundIntensity.size(); i++) {
			mean	+= backgroundIntensity[i];
		}
		mean	/= backgroundIntensity.size();
		cout<<"mean : "<<mean<<endl;

		sigma	= 0.f;
		for (int i = 0; i < backgroundIntensity.size(); i++) {
			sigma	+= pow(backgroundIntensity[i] - mean, 2);
		}
		sigma	/= backgroundIntensity.size();
		cout<<"sigma : "<<sigma<<endl;

		for (int i = 0; i <= 255; i++) {
			float	value	= (1 / sqrt(2 * PI * sigma)) * exp(-1 * pow(i - mean, 2) / (2 * sigma));
			backgroundDistribution.push_back(Point2f(i, value));	
		}
		float	foregroundExpectation	= 0.f;
		float	backgroundExpectation	= 0.f; 
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int i = 0; i < foregroundDistribution.size(); i++) {
					if (foregroundDistribution[i].x	== clock.at<uchar>(y, x)) {
						foregroundExpectation	= foregroundDistribution[i].y;
					} else{} 
					if (backgroundDistribution[i].x	== clock.at<uchar>(y, x)) {
						backgroundExpectation	= backgroundDistribution[i].y;
					} else{}	
				}		
				if (foregroundExpectation > backgroundExpectation) {
					binarySegmentation.at<uchar>(y, x) = 255;
				} else {
					binarySegmentation.at<uchar>(y, x) = 0;
				}
			}
		}
		//imshow("binary", binarySegmentation);
		//waitKey(0);
	}
}