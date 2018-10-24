#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "filterParallel.h"

void applyThread(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int tid, int numThreads) {		
	//VARIABLE DECLARATIONS
	int i = 0; //ROW INDEX
	int j = 0; //COLUMN INDEX
	Pixel fa; //[0][0] TEMP
	Pixel fb; //[0][1] TEMP
	Pixel fc; //[0][2] TEMP
	Pixel fd; //[1][0] TEMP
	Pixel fe; //[1][1] TEMP
	Pixel ff; //[1][2] TEMP
	Pixel fg; //[2][0] TEMP
	Pixel fh; //[2][1] TEMP
	Pixel fi; //[2][2] TEMP
	////////////APPLY FUNCTION IMPLEMENTED IN PA13 WITH MODIFICATION///////////////
	int intervalLength = (imageIn->norm_height + numThreads - 1) / numThreads;
	int lowBound = tid * intervalLength;
	int highBound = lowBound + intervalLength;
	//IN CASE highBound EXCEEDS THE ACTUAL HEIGHT, CLIP IT TO HEIGHT (PREVENT SEG-FAULT)
	if(highBound > imageIn->norm_height)
	{
		highBound = imageIn->norm_height;
	}
	//INSTEAD OF STARTING ROW INDEX FROM 0, START WITH lowBound
	//AND END WITH highBound-1 (modification from PA13)
	for(i = lowBound; i < highBound; i++)
	{
		for(j = 0; j < (int) imageOut->header.width_px; j++)
		{
			//LEFT TOP CORNER
			if( (i - 1) < 0 && (j - 1) < 0 )
			{
				fa = imageIn->pixels[i][j];
				fb = imageIn->pixels[i][j];
				fc = imageIn->pixels[i][j+1];
				fd = imageIn->pixels[i][j];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j+1];
				fg = imageIn->pixels[i+1][j];
				fh = imageIn->pixels[i+1][j];
				fi = imageIn->pixels[i+1][j+1];
			}
			//RIGHT TOP CORNER
			else if( (i - 1) < 0 && (j + 1) == (int) imageOut->header.width_px )
			{	
				fa = imageIn->pixels[i][j-1];
				fb = imageIn->pixels[i][j];
				fc = imageIn->pixels[i][j];
				fd = imageIn->pixels[i][j-1];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j];
				fg = imageIn->pixels[i+1][j-1];
				fh = imageIn->pixels[i+1][j];
				fi = imageIn->pixels[i+1][j];
			}
			//LEFT BOTTOM CORNER
			else if( (i + 1) == imageOut->norm_height && (j - 1) < 0 )
			{
				fa = imageIn->pixels[i-1][j];
				fb = imageIn->pixels[i-1][j];
				fc = imageIn->pixels[i-1][j+1];
				fd = imageIn->pixels[i][j];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j+1];
				fg = imageIn->pixels[i][j];
				fh = imageIn->pixels[i][j];
				fi = imageIn->pixels[i][j+1];
			}
			//RIGHT BOTTOM CORNER
			else if( (i + 1) == imageOut->norm_height && (j + 1) == (int) imageOut->header.width_px )
			{	
				fa = imageIn->pixels[i-1][j-1];
				fb = imageIn->pixels[i-1][j];
				fc = imageIn->pixels[i-1][j];
				fd = imageIn->pixels[i][j-1];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j];
				fg = imageIn->pixels[i][j-1];
				fh = imageIn->pixels[i][j];
				fi = imageIn->pixels[i][j];
			}
			//TOP
			else if( (i - 1) < 0 )
			{
				fa = imageIn->pixels[i][j-1];
				fb = imageIn->pixels[i][j];
				fc = imageIn->pixels[i][j+1];
				fd = imageIn->pixels[i][j-1];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j+1];
				fg = imageIn->pixels[i+1][j-1];
				fh = imageIn->pixels[i+1][j];
				fi = imageIn->pixels[i+1][j+1];
			}
			//LEFT
			else if( (j - 1) < 0 )
			{
				fa = imageIn->pixels[i-1][j];
				fb = imageIn->pixels[i-1][j];
				fc = imageIn->pixels[i-1][j+1];
				fd = imageIn->pixels[i][j];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j+1];
				fg = imageIn->pixels[i+1][j];
				fh = imageIn->pixels[i+1][j];
				fi = imageIn->pixels[i+1][j+1];
			}
			//RIGHT
			else if( (j + 1) == (int) imageOut->header.width_px )
			{
				fa = imageIn->pixels[i-1][j-1];
				fb = imageIn->pixels[i-1][j];
				fc = imageIn->pixels[i-1][j];
				fd = imageIn->pixels[i][j-1];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j];
				fg = imageIn->pixels[i+1][j-1];
				fh = imageIn->pixels[i+1][j];
				fi = imageIn->pixels[i+1][j];
			}
			//BOTTOM
			else if( (i + 1) == imageOut->norm_height )
			{
				fa = imageIn->pixels[i-1][j-1];
				fb = imageIn->pixels[i-1][j];
				fc = imageIn->pixels[i-1][j+1];
				fd = imageIn->pixels[i][j-1];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j+1];
				fg = imageIn->pixels[i][j-1];
				fh = imageIn->pixels[i][j];
				fi = imageIn->pixels[i][j+1];
			}
			//BASE CASE
			else
			{
				fa = imageIn->pixels[i-1][j-1];
				fb = imageIn->pixels[i-1][j];
				fc = imageIn->pixels[i-1][j+1];
				fd = imageIn->pixels[i][j-1];
				fe = imageIn->pixels[i][j];
				ff = imageIn->pixels[i][j+1];
				fg = imageIn->pixels[i+1][j-1];
				fh = imageIn->pixels[i+1][j];
				fi = imageIn->pixels[i+1][j+1];
			}
			///////////
			int blue = ( (int)fa.blue * f.filter[0][0] + (int)fb.blue * f.filter[0][1] + (int)fc.blue * f.filter[0][2] + (int)fd.blue * f.filter[1][0] + (int)fe.blue * f.filter[1][1] + (int)ff.blue * f.filter[1][2] + (int)fg.blue * f.filter[2][0] + (int)fh.blue * f.filter[2][1] + (int)fi.blue * f.filter[2][2]) / f.norm;
			if(blue > 255)
			{
				imageOut->pixels[i][j].blue = 255;
			}
			else if(blue < 0)
			{
				imageOut->pixels[i][j].blue = 0;
			}
			else
			{
				imageOut->pixels[i][j].blue = blue;
			}
			int green = ((int)fa.green * f.filter[0][0] + (int)fb.green * f.filter[0][1] + (int)fc.green * f.filter[0][2] + (int)fd.green * f.filter[1][0] + (int)fe.green * f.filter[1][1] + (int)ff.green * f.filter[1][2] + (int)fg.green * f.filter[2][0] + (int)fh.green * f.filter[2][1] + (int)fi.green * f.filter[2][2]) / f.norm;
			if(green > 255)
			{
				imageOut->pixels[i][j].green = 255;
			}
			else if(green < 0)
			{
				imageOut->pixels[i][j].green = 0;
			}
			else
			{
				imageOut->pixels[i][j].green = green;
			}
			int red = ((int)fa.red * f.filter[0][0] + (int)fb.red * f.filter[0][1] + (int)fc.red * f.filter[0][2] + (int)fd.red * f.filter[1][0] + (int)fe.red * f.filter[1][1] + (int)ff.red * f.filter[1][2] + (int)fg.red * f.filter[2][0] + (int)fh.red * f.filter[2][1] + (int)fi.red * f.filter[2][2]) / f.norm;
			if(red > 255)
			{
				imageOut->pixels[i][j].red = 255;
			}
			else if(red < 0)
			{
				imageOut->pixels[i][j].red = 0;
			}
			else
			{
				imageOut->pixels[i][j].red = red;
			}
			int alpha = ((int)fa.alpha * f.filter[0][0] + (int)fb.alpha * f.filter[0][1] + (int)fc.alpha * f.filter[0][2] + (int)fd.alpha * f.filter[1][0] + (int)fe.alpha * f.filter[1][1] + (int)ff.alpha * f.filter[1][2] + (int)fg.alpha * f.filter[2][0] + (int)fh.alpha * f.filter[2][1] + (int)fi.alpha * f.filter[2][2]) / f.norm;
			if(alpha > 255)
			{
				imageOut->pixels[i][j].alpha = 255;
			}
			else if(alpha < 0)
			{
				imageOut->pixels[i][j].alpha = 0;
			}
			else
			{
				imageOut->pixels[i][j].alpha = alpha;
			}
		}
	}
	//FILL IN. This is the work that thread #tid should do
	//You may find it useful to know the number of threads (numThreads) to
	//figure out what to do.
}

void * applyThreadWrapper(void * args) {
	ApplyArgs * applyArgs = (ApplyArgs *) args;
	fprintf(stdout, "calling thread %d\n", applyArgs->tid);
	
	applyThread(applyArgs->in, applyArgs->out, applyArgs->filter, applyArgs->tid, applyArgs->numThreads);
	
	fprintf(stdout, "finished with thread %d\n", applyArgs->tid);
	
	return NULL;
}

void apply(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int numThreads) {
	pthread_t * threads = malloc(sizeof(pthread_t) * numThreads);
	ApplyArgs * args = malloc(sizeof(ApplyArgs) * numThreads);
	int i;
	for(i = 0; i < numThreads; i++)
	{
		args[i].in = imageIn;
		args[i].out = imageOut;
		args[i].filter = f;
		args[i].tid = i;
		args[i].numThreads = numThreads;
	}
	for(i = 0; i < numThreads; i++)
	{
		pthread_create(&threads[i], NULL, applyThreadWrapper, &args[i]);
	}
	for(i = 0; i < numThreads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	free(threads);
	free(args);
	//1. create numThreads threads, that each call applyThreadWrapper
	//2. wait for all threads to finish
	//3. clean up any memory allocation you did.
}
