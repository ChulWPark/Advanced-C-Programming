#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "filterParallel.h"

#define SINGLE_PIXEL_ABS_TOLERANCE 20
#define PIXELS_PERCENTAGE_ALLOWED 2

int main(int argc, char ** argv) {
	if (argc != 3) {
	fprintf(stderr, "Usage ./pa13 actual.bmp expected.bmp\n");
	return EXIT_FAILURE;
	}
	
	FILE * actualFile = fopen(argv[1], "r");
	FILE * expectedFile = fopen(argv[2], "w");
	
	BoxFilter f;
	f.filter[0][0] = -1;
	f.filter[0][1] = 0;
	f.filter[0][2] = 1;
	f.filter[1][0] = -1;
	f.filter[1][1] = 0;
	f.filter[1][2] = 1;
	f.filter[2][0] = -1;
	f.filter[2][1] = 0;
	f.filter[2][2] = 1;
	f.norm = 1.0;

	int numThreads = 32;
	
	BMPImage * in = readImage(actualFile);
	fseek(actualFile,0,SEEK_SET);
	BMPImage * out = readImage(actualFile);
	apply(in,out,f,numThreads);
	writeImage(out,expectedFile);

	freeImage(in);
	freeImage(out);
	
	fclose(actualFile);
	fclose(expectedFile);
}
