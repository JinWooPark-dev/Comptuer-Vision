/**
	@mainpage   Computer Vison Assignment
	@brief      Clustering and Segmentation 

	@section    detail Detailed Description
	@details    include k-means clustering and image segmentation using k-means and mean-shift.

	@section    author Author Information
	@author     Jinwoo Park
	@date       2020-07-25
*/

#include "clustering.h"

void k_meansClustering (const	Mat inputImage,			///< inputImage
								Mat &outputImage,		///< outputImage
								vector<Point2f> point)	///< circle Point 
{	
	const	int width	= inputImage.cols;
	const	int height	= inputImage.rows;

	int	groupingNum	= 3;
	double	countGroup[3]	= {0,};

	vector<Point2f>	k(groupingNum);
	vector<Point2f>	center(groupingNum);

	vector<vector<double>> distance(groupingNum);
	for (int i = 0; i < groupingNum; i++) {
		distance[i].resize(point.size());
	}

	for(int i = 0; i < groupingNum; i++){
		Point2f tmp;
		tmp.x = (double)(rand() % width);
		tmp.y = (double)(rand() % height);
		k[i] = tmp;
	}
	
	bool loop = true;
	
	while(loop) {

		for (int i = 0; i < 3; i++) {
			center[i].x	= 0;
			center[i].y	= 0;
			countGroup[i]	= 0;
		}

		for (int i = 0; i < point.size(); i++) {
			for (int j = 0; j < groupingNum; j++) {
				double tmpDistance	= sqrt(pow(k[j].x - point[i].x, 2) + pow(k[j].y - point[i].y, 2));
				distance[j][i] = tmpDistance;
			}
		}

		for (int i = 0; i < point.size(); i++) {
			double	min = distance[0][i];
			int minj = 0;

			for (int j = 1; j < groupingNum; j++) {
				if (min > distance[j][i]) {
					min = distance[j][i];
					minj = j;
				} else{}
			}

			center[minj].x	+= point[i].x;
			center[minj].y	+= point[i].y;

			countGroup[minj]++;

			if (minj == 0) {
				circle(outputImage, point[i], 2, Scalar(255, 0, 0), 2);
			}
			else if (minj == 1) {
				circle(outputImage, point[i], 2, Scalar(0, 255, 0), 2);

			}
			else if (minj == 2) {
				circle(outputImage, point[i], 2, Scalar(0, 0, 255), 2);
			} else{}
		}

		int sameCount	= 0;
		for (int i = 0; i < groupingNum; i++) {
			if (countGroup[i] != 0) {
				
				if (float((center[i].x / countGroup[i])) == k[i].x && float((center[i].y / countGroup[i])) == k[i].y) {
					sameCount++;
				} else{}

				k[i].x = center[i].x / countGroup[i];
				k[i].y = center[i].y / countGroup[i];
			} else{}
		}

		if (sameCount == 3) {
			loop = false;
		} else{}
	}
}