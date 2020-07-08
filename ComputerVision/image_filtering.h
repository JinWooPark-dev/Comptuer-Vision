#ifndef IMAGE_FILTERING_H
#define IMAGE_FILTERING_H

#include "header.h"


/// filtering the image using box methond
void boxFiltering(const Mat input,			///< inputImage
						Mat output,			///< outputImage
						int filterSizeX,	///< filterSizeX
						int filterSizeY);	///< filterSizeY
#endif