/**
	@mainpage   Computer Vison Assignment
	@brief      Stereo Matching sourcefile

	@section    detail Detailed Description
	@details    include Stereo Matching.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-08-11
*/

#include "stereo_matching.h"

/// stereo matching using ssd(sum of squared difference)
void windowMatching	(	const	Mat leftImage,		///< leftImage
						const	Mat rightImage,		///< rightImage
								Mat	&disparityMap,	///< disparityMap
						const	int	windowSize,		///< windowsize
						const	int maxDisparity)	///< max Disparity
{
	const	int	width	= leftImage.cols;
	const	int	height	= leftImage.rows;
	
	vector<vector<vector<float>>>	costMap(height);
	for (int i = 0; i < height; i++) {
		costMap[i].resize(width);
		for (int j = 0; j < width; j++) {
			costMap[i][j].resize(maxDisparity);
		}
	}
	for (int y = int(windowSize / 2); y < height - int(windowSize / 2); y++) {
		for (int x = int(windowSize / 2); x < width - int(windowSize / 2); x++) {					
			for (int i = -(maxDisparity / 2); i < (maxDisparity / 2); i++) {
				float	value	= 0.f;
				for(int j = -int(windowSize / 2); j <= int(windowSize / 2); j++) {
					for (int k = -int(windowSize / 2); k <= int(windowSize / 2); k++) {
						if (x + k + i < width && x + k + i >= 0) {
							value	+= pow(leftImage.at<uchar>(y + j, x + k) - rightImage.at<uchar>(y + j, x + k + i), 2);
						} else{}
					}
				}
				costMap[y][x][i + (maxDisparity / 2)]	= value;
			}
		}
	}
	for (int y = int(windowSize / 2); y < height - int(windowSize / 2); y++) {
		for (int x = int(windowSize / 2); x < width - int(windowSize / 2); x++) {
			float	minCostMap	= 999999.f;
			int		index		= 0;
			for (int i = 0; i < maxDisparity; i++) {
				if (costMap[y][x][i] > 0) {
					if (minCostMap > costMap[y][x][i]) {
						minCostMap	= costMap[y][x][i];
						index		= i;
					} else{}

				} else{}
			}
			if (index >= (maxDisparity / 2)) {
				index	-= (maxDisparity / 2);
			} else {
				index	= abs(index	- ((maxDisparity / 2) - 1));
			}
			if (x >= (maxDisparity / 2)) {
				disparityMap.at<float>(y, x) = index * (255 / maxDisparity);
			} else{}
		}
	}
	disparityMap.convertTo(disparityMap, CV_8U);
}