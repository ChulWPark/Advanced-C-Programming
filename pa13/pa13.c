#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bmp.h"
#include "filter.h"

#define SINGLE_PIXEL_ABS_TOLERANCE 20
#define PIXELS_PERCENTAGE_ALLOWED 2

int main(int argc, char ** argv) {
	if (argc != 4) {
	fprintf(stderr, "Usage ./pa13 actual.bmp expected.bmp\n");
	return EXIT_FAILURE;
	}
	
	FILE * actualFile = fopen(argv[1], "r");
	FILE * expectedFile = fopen(argv[2], "w");
	FILE * filterFile = fopen(argv[3], "r");

	BoxFilter * filter = readFilter(filterFile);	
	printf("%d ", filter->filter[0][0]);
	printf("%d ", filter->filter[0][1]);
	printf("%d\n", filter->filter[0][2]);
	printf("%d ", filter->filter[1][0]);
	printf("%d ", filter->filter[1][1]);
	printf("%d\n", filter->filter[1][2]);
	printf("%d ", filter->filter[2][0]);
	printf("%d ", filter->filter[2][1]);
	printf("%d\n", filter->filter[2][2]);
	printf("%f\n", filter->norm);
	BoxFilter temp;
	temp.filter[0][0] = filter->filter[0][0];
	temp.filter[0][1] = filter->filter[0][1];
	temp.filter[0][2] = filter->filter[0][2];
	temp.filter[1][0] = filter->filter[1][0];
	temp.filter[1][1] = filter->filter[1][1];
	temp.filter[1][2] = filter->filter[1][2];
	temp.filter[2][0] = filter->filter[2][0];
	temp.filter[2][1] = filter->filter[2][1];
	temp.filter[2][2] = filter->filter[2][2];
	temp.norm = filter->norm;
	BMPImage * sajin = readImage(actualFile);
	BMPImage * filtered = apply(sajin, temp);
	writeImage(filtered, expectedFile);
	
	free(filter);
	freeImage(sajin);
	freeImage(filtered);
	fclose(actualFile);
	fclose(expectedFile);
	fclose(filterFile);
}
