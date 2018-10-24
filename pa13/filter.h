#ifndef FILTER_H_
#define FILTER_H_

#include "bmp.h"

typedef struct BoxFilter {
	int filter[3][3];
	float norm;
} BoxFilter;

//Apply blur box filter to input image, return pointer to blurred image
BMPImage * blur(BMPImage * image);

//EXTRA CREDIT
//Apply arbitrary 3x3 box filter to input image, return pointer
BMPImage * apply(BMPImage * image, BoxFilter f);

//Read in a box filter spec from the given input file
BoxFilter * readFilter(FILE * infile);

#endif
