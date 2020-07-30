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

void imageSegmentation(const	Mat inputImage,		///< inputImage
								Mat &outputImage,	///< outputImage
								int kValue)			///< kvalue
{
	const int width		= inputImage.cols;
	const int height	= inputImage.rows;

	vector<Mat> rgbImage(3);
	split(inputImage, rgbImage);

	Mat B	= Mat::zeros(height, width, CV_8UC1);
	Mat G	= Mat::zeros(height, width, CV_8UC1);
	Mat R	= Mat::zeros(height, width, CV_8UC1);

	int groupingNum	= kValue;
	double countGroup[15] = {0,};

	vector<Point3f> k(groupingNum);
	vector<Point3f> center(groupingNum);

	vector<vector<vector<double>>> distance(groupingNum);
	for (int i = 0; i < groupingNum; i++) {
		distance[i].resize(height);
	}
	for (int i = 0; i < groupingNum; i++) {
		for (int j = 0; j < height; j++) {
			distance[i][j].reserve(width);
		}
	}

	for (int i = 0; i < groupingNum; i++) {
		Point2f tmp;
		tmp.x	= (double)(rand() % width);
		tmp.y	= (double)(rand() % height);
		k[i].x	= rgbImage[0].at<uchar>(tmp.y, tmp.x); ///< B Value
		k[i].y	= rgbImage[1].at<uchar>(tmp.y, tmp.x); ///< G Value
		k[i].z	= rgbImage[2].at<uchar>(tmp.y, tmp.x); ///< R Value
	}

	bool loop = true;

	while (loop) {
		for (int i = 0; i < groupingNum; i++) {
			center[i].x	= 0;
			center[i].y	= 0;
			center[i].z = 0;
			countGroup[i] = 0;
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int j = 0; j < groupingNum; j++) {
					double tmpDistance	= sqrt(pow(k[j].x - rgbImage[0].at<uchar>(y, x), 2) + pow(k[j].y - rgbImage[1].at<uchar>(y, x), 2) + pow(k[j].z - rgbImage[2].at<uchar>(y, x), 2));
					distance[j][y][x] = tmpDistance;
				}
			}
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				double min	= distance[0][y][x];
				int minj	= 0;

				for (int j = 1; j < groupingNum; j++) {
					if (min > distance[j][y][x]) {
						min	= distance[j][y][x];
						minj = j;
					} else {}
				}

				center[minj].x	+= rgbImage[0].at<uchar>(y, x);
				center[minj].y	+= rgbImage[1].at<uchar>(y, x);
				center[minj].z	+= rgbImage[2].at<uchar>(y, x);

				B.at<uchar>(y, x) = k[minj].x;
				G.at<uchar>(y, x) = k[minj].y;
				R.at<uchar>(y, x) = k[minj].z;

				countGroup[minj]++;
			}
		}

		int sameCount = 0; 
		for (int i = 0; i < groupingNum; i++) {
			if (countGroup[i] != 0) {
				if (float((center[i].x / countGroup[i])) == k[i].x && float((center[i].y / countGroup[i])) == k[i].y && float((center[i].z / countGroup[i])) == k[i].z) {
					sameCount++;
					cout<<"sameCount "<<sameCount<<endl;
				} else{}

				k[i].x = center[i].x / countGroup[i];
				k[i].y = center[i].y / countGroup[i];
				k[i].z = center[i].z / countGroup[i];
			} else{}
		}
		if (sameCount > 3) {
			loop = false;
		} else{}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			outputImage.at<Vec3b>(y,x)[0]	= B.at<uchar>(y,x);
			outputImage.at<Vec3b>(y,x)[1]	= G.at<uchar>(y,x); 
			outputImage.at<Vec3b>(y,x)[2]	= R.at<uchar>(y,x); 
		}
	}
}

void imageSegmentationUsingColorSpace_Location(const	Mat inputImage,		///< inputImage
														Mat &outputImage,	///< outputImage
														int kValue)			///< k value
{
	const	int	width	= inputImage.cols;
	const	int	height	= inputImage.rows;

	vector<Mat> rgbImage(3);
	split(inputImage, rgbImage);

	Mat B	= Mat::zeros(height, width, CV_8UC1);
	Mat G	= Mat::zeros(height, width, CV_8UC1);
	Mat R	= Mat::zeros(height, width, CV_8UC1);

	int groupingNum	= kValue;
	double countGroup[15] = {0,};

	vector<Mat>	kMat(groupingNum);
	vector<Mat>	centerMat(groupingNum);

	for (int i = 0; i < groupingNum; i++) {
		kMat[i]			= Mat::zeros(1, 5, CV_32F);
		centerMat[i]	= Mat::zeros(1, 5, CV_32F);	
	}

	vector<vector<vector<double>>>	distance(groupingNum);
	for (int i = 0; i < groupingNum; i++) {
		distance[i].resize(height);
	}
	for (int i = 0; i < groupingNum; i++) {
		for (int j = 0; j < height; j++) {
			distance[i][j].resize(width);
		}
	}

	for (int i = 0; i < groupingNum; i++) {
		Point2f tmp;
		tmp.x	= (double)(rand() % width);
		tmp.y	= (double)(rand() % height);
		kMat[i].at<float>(0, 0)	= rgbImage[0].at<uchar>(tmp.y, tmp.x);
		kMat[i].at<float>(0, 1)	= rgbImage[1].at<uchar>(tmp.y, tmp.x);
		kMat[i].at<float>(0, 2)	= rgbImage[2].at<uchar>(tmp.y, tmp.x);
		kMat[i].at<float>(0, 3)	= tmp.x;
		kMat[i].at<float>(0, 4)	= tmp.y;
	}

	bool loop = true;

	while (loop) {

		for (int i = 0; i < groupingNum; i++ ) {
			centerMat[i].at<float>(0, 0) = 0;
			centerMat[i].at<float>(0, 1) = 0;
			centerMat[i].at<float>(0, 2) = 0;
			centerMat[i].at<float>(0, 3) = 0;
			centerMat[i].at<float>(0, 4) = 0;
			countGroup[i] = 0;
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int j = 0; j < groupingNum; j++) {
					double tmpDistance	= sqrt( pow( kMat[j].at<float>(0, 0) - rgbImage[0].at<uchar>(y, x), 2) + pow(kMat[j].at<float>(0, 1) - rgbImage[1].at<uchar>(y, x), 2) 
												+ pow(kMat[j].at<float>(0, 2) - rgbImage[2].at<uchar>(y, x), 2) + pow(kMat[j].at<float>(0, 3) - x, 2) + pow(kMat[j].at<float>(0, 4) - y, 2));
					distance[j][y][x] = tmpDistance;
				}
			}
		}
	
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				double min = distance[0][y][x];
				int minj	= 0;

				for (int j = 1; j < groupingNum; j++) {
					if (min > distance[j][y][x]) {
						min = distance[j][y][x];
						minj = j;
					} else{}
				}

				centerMat[minj].at<float>(0, 0) += rgbImage[0].at<uchar>(y, x);
				centerMat[minj].at<float>(0, 1) += rgbImage[1].at<uchar>(y, x);
				centerMat[minj].at<float>(0, 2) += rgbImage[2].at<uchar>(y, x);
				centerMat[minj].at<float>(0, 3) += x;
				centerMat[minj].at<float>(0, 4) += y;

				B.at<uchar>(y, x) = kMat[minj].at<float>(0, 0);
				G.at<uchar>(y, x) = kMat[minj].at<float>(0, 1);
				R.at<uchar>(y, x) = kMat[minj].at<float>(0, 2);

				countGroup[minj]++;
			}
		}

		int sameCount = 0; 
		for (int i = 0; i < groupingNum; i++) {
			if (countGroup[i] != 0) {

				if (float((centerMat[i].at<float>(0, 0) / countGroup[i])) == kMat[i].at<float>(0, 0) && float((centerMat[i].at<float>(0, 1) / countGroup[i])) == kMat[i].at<float>(0, 1) 
					&& float((centerMat[i].at<float>(0, 2) / countGroup[i])) == kMat[i].at<float>(0, 2) && float((centerMat[i].at<float>(0, 3) / countGroup[i])) == kMat[i].at<float>(0, 3)
					&& float((centerMat[i].at<float>(0, 4) / countGroup[i])) == kMat[i].at<float>(0, 4)) {
					sameCount++;
				} else{}

				kMat[i].at<float>(0, 0) = centerMat[i].at<float>(0, 0) / countGroup[i];
				kMat[i].at<float>(0, 1) = centerMat[i].at<float>(0, 1) / countGroup[i];
				kMat[i].at<float>(0, 2) = centerMat[i].at<float>(0, 2) / countGroup[i];
				kMat[i].at<float>(0, 3) = centerMat[i].at<float>(0, 3) / countGroup[i];
				kMat[i].at<float>(0, 4) = centerMat[i].at<float>(0, 4) / countGroup[i];
			} else{}
		}
		if (sameCount > 3) {
			loop = false;
		} else{}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			outputImage.at<Vec3b>(y,x)[0]	= B.at<uchar>(y,x);
			outputImage.at<Vec3b>(y,x)[1]	= G.at<uchar>(y,x); 
			outputImage.at<Vec3b>(y,x)[2]	= R.at<uchar>(y,x); 
		}
	}
}

void imageSegmentationUsingMeanShift(const	Mat inputImage,		///<inputImage
											Mat &outputImage)	///<outputImage
{
	const	int	width	= inputImage.cols;
	const	int	height	= inputImage.rows;

	vector<Mat> rgbImage(3);
	split(inputImage, rgbImage);

	Mat BValue	= Mat::zeros(height, width, CV_8UC1);
	Mat GValue	= Mat::zeros(height, width, CV_8UC1);
	Mat RValue	= Mat::zeros(height, width, CV_8UC1);

	int groupingNum	= 30;
	double countGroup[30] = {0,};

	vector<Mat>	kMat(groupingNum);
	vector<Mat>	centerMat(groupingNum);

	for (int i = 0; i < groupingNum; i++) {
		kMat[i]			= Mat::zeros(1, 3, CV_32F);
		centerMat[i]	= Mat::zeros(1, 3, CV_32F);	
	}

	vector<vector<vector<double>>>	distance(groupingNum);
	for (int i = 0; i < groupingNum; i++) {
		distance[i].resize(height);
		for (int j = 0; j < height; j++) {
			distance[i][j].resize(width);
		}
	}

	for (int i = 0; i < groupingNum; i++) {
		Point2f tmp;
		tmp.x	= (double)(rand() % width);
		tmp.y	= (double)(rand() % height);
		
		if ( i == 0 ) {
		kMat[i].at<float>(0, 0)	= rgbImage[0].at<uchar>(237, 178);
		kMat[i].at<float>(0, 1)	= rgbImage[1].at<uchar>(237, 178);
		kMat[i].at<float>(0, 2)	= rgbImage[2].at<uchar>(237, 178);

		}
		else {
		kMat[i].at<float>(0, 0)	= rgbImage[0].at<uchar>(tmp.y, tmp.x);
		kMat[i].at<float>(0, 1)	= rgbImage[1].at<uchar>(tmp.y, tmp.x);
		kMat[i].at<float>(0, 2)	= rgbImage[2].at<uchar>(tmp.y, tmp.x);
		}
	}

	bool loop = true;

	while (loop) {

		for (int i = 0; i < groupingNum; i++ ) {
			centerMat[i].at<float>(0, 0) = 0;
			centerMat[i].at<float>(0, 1) = 0;
			centerMat[i].at<float>(0, 2) = 0;
			countGroup[i] = 0;
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				for (int j = 0; j < groupingNum; j++) {
					double tmpDistance	= sqrt(pow(kMat[j].at<float>(0, 0) - rgbImage[0].at<uchar>(y, x), 2) + pow(kMat[j].at<float>(0, 1) - rgbImage[1].at<uchar>(y, x), 2) 
												+ pow(kMat[j].at<float>(0, 2) - rgbImage[2].at<uchar>(y, x), 2));
					distance[j][y][x] = tmpDistance;
				}
			}
		}

		for (int i = 0; i < groupingNum; i++) {

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					if (distance[i][y][x] < 20) {
						centerMat[i].at<float>(0, 0) += rgbImage[0].at<uchar>(y, x);
						centerMat[i].at<float>(0, 1) += rgbImage[1].at<uchar>(y, x);
						centerMat[i].at<float>(0, 2) += rgbImage[2].at<uchar>(y, x);

						BValue.at<uchar>(y, x) = kMat[i].at<float>(0, 0);
						GValue.at<uchar>(y, x) = kMat[i].at<float>(0, 1);
						RValue.at<uchar>(y, x) = kMat[i].at<float>(0, 2);

						countGroup[i]++;
					} else{}
				}
			}
		}
		int sameCount = 0; 
		for (int i = 0; i < groupingNum; i++) {
			if (countGroup[i] != 0) {

				if (float((centerMat[i].at<float>(0, 0) / countGroup[i])) == kMat[i].at<float>(0, 0) && float((centerMat[i].at<float>(0, 1) / countGroup[i])) == kMat[i].at<float>(0, 1) 
					&& float((centerMat[i].at<float>(0, 2) / countGroup[i])) == kMat[i].at<float>(0, 2)) {
					sameCount++;
					cout<<"sameCount "<<sameCount<<endl;
				} else{}

				kMat[i].at<float>(0, 0) = centerMat[i].at<float>(0, 0) / countGroup[i];
				kMat[i].at<float>(0, 1) = centerMat[i].at<float>(0, 1) / countGroup[i];
				kMat[i].at<float>(0, 2) = centerMat[i].at<float>(0, 2) / countGroup[i];
			} else{}
		}
		if (sameCount > 3) {
			loop = false;
		} else{}
	}

	vector<vector<int>>	groupIndex(height);
	for (int i = 0; i < height; i++) {
		groupIndex[i].resize(width);
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float	minDistance	= 9999999.f;
			for (int i = 0; i < groupingNum; i++) {
				float	distance	= SQR(inputImage.at<Vec3b>(y, x)[0] - kMat[i].at<float>(0, 0))
									+ SQR(inputImage.at<Vec3b>(y, x)[1] - kMat[i].at<float>(0, 1))
									+ SQR(inputImage.at<Vec3b>(y, x)[2] - kMat[i].at<float>(0, 2));
				if (distance < minDistance) {
					minDistance			= distance;
					groupIndex[y][x]	= i;
				} else{}
			}
		}
	}

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			outputImage.at<Vec3b>(y,x)[0]	= kMat[groupIndex[y][x]].at<float>(0, 0);
			outputImage.at<Vec3b>(y,x)[1]	= kMat[groupIndex[y][x]].at<float>(0, 1);
			outputImage.at<Vec3b>(y,x)[2]	= kMat[groupIndex[y][x]].at<float>(0, 2);
		}
	}
}