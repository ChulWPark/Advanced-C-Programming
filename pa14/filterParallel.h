#ifndef FILTER_H_
#define FILTER_H_

#include "bmp.h"

typedef struct BoxFilter {
	int filter[3][3];
	float norm;
} BoxFilter;

typedef struct ApplyArgs {
	BMPImage * in;
	BMPImage * out;
	BoxFilter filter;
	int tid;
	int numThreads;
} ApplyArgs;

void applyThread(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int tid, int numThreads);

void * applyThreadWrapper(void * args);

void apply(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int numThreads);

#endif
