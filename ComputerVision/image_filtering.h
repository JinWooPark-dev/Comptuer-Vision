#ifndef IMAGE_FILTERING_H
#define IMAGE_FILTERING_H

#include "header.h"


/// filtering the image using box methond
void boxFiltering(const Mat input,			///< inputImage
						Mat output,			///< outputImage
						int filterSizeX,	///< filterSizeX
						int filterSizeY);	///< filterSizeY

/// filtering the image using gaussian methond
void gaussianFiltering(const	Mat input,			///< inputImage
								Mat output,			///< outputImage
								int filterSizeX,	///< filterSizeX
								int filterSizeY);	///< filterSizeY

/// filtering the image using separable gaussian methond
void separableKernel(const	Mat input,			///< inputImage
							Mat output,			///< outputImage
							int filterSizeX,		///< filterSizeX
							int filterSizeY);		///< filterSizeY

/// make the sharpening image
void imageSharpening(const	Mat input,			///< inputImage	
							Mat output,			///< outputImage
							int filterSizeX,		///< filterSizeX
							int filterSizeY);		///< filterSizeY

/// make salt and pepper noise image
void saltPepperNoise(const	Mat input,				///< inputImage	
							Mat output,				///< outputImage
							double noiseRatio);		///< percentage of noiseratio

/// make gaussian noise image
void gaussianNoise(const	Mat input,		///< inputImage	
							Mat output);		///< outputImage
#endif