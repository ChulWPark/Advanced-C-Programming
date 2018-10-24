#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp) {
	//malloc the image structure
	BMPImage * init = malloc(sizeof(BMPImage));
	//declare temp variables
	uint16_t temp16;
	uint32_t temp32;
	int32_t ttemp32;
	//store the values of header attribute
	//TYPE
	fread(&temp16, 1, 2, fp);
	init->header.type = temp16;
	//SIZE
	fread(&temp32, 2, 2, fp);
	init->header.size = temp32;
	//RESERVED1
	fread(&temp16, 1, 2, fp);
	init->header.reserved1 = temp16;
	//RESERVED2
	fread(&temp16, 1, 2, fp);
	init->header.reserved2 = temp16;
	//OFFSET
	fread(&temp32, 2, 2, fp);
	init->header.offset = temp32;
	//DIB_HEADER_SIZE
	fread(&temp32, 2, 2, fp);
	init->header.dib_header_size = temp32;
	//WIDTH_PX
	fread(&ttemp32, 2, 2, fp);
	init->header.width_px = ttemp32;
	//HEIGHT_PX
	fread(&ttemp32, 2, 2, fp);
	init->header.height_px = ttemp32;
	//NUM_PLANES
	fread(&temp16, 2, 1, fp);
	init->header.num_planes = temp16;
	//BITS_PER_PIXEL
	fread(&temp16, 2, 1, fp);
	init->header.bits_per_pixel = temp16;
	//COMPRESSION
	fread(&temp32, 2, 2, fp);
	init->header.compression = temp32;
	//IMAGE_SIZE_BYTES
	fread(&temp32, 2, 2, fp);
	init->header.image_size_bytes = temp32;
	//X_RESOLUTION_PPM
	fread(&ttemp32, 2, 2, fp);
	init->header.x_resolution_ppm = ttemp32;
	//Y_RESOLUTION_PPM
	fread(&ttemp32, 2, 2, fp);
	init->header.y_resolution_ppm = ttemp32;
	//NUM_COLORS
	fread(&temp32, 2, 2, fp);
	init->header.num_colors = temp32;
	//IMPORTANT_COLORS
	fread(&temp32, 2, 2, fp);
	init->header.important_colors = temp32;
	//NORM_HEIGHT	
	if(init->header.height_px < 0)
	{
		init->norm_height = (int) (init->header.height_px * -1);
	}
	else
	{
		init->norm_height = (int) init->header.height_px;
	}
	//BUILD 2D ARRAY
	init->pixels = malloc(init->norm_height * sizeof(Pixel *));
	int row;
	for(row = 0; row < init->norm_height; row++)
	{
		init->pixels[row] = malloc( (int)init->header.width_px * sizeof(Pixel));
	}
	//STORE VALUES INTO THE 2D ARRAY "PIXEL"
	if((int) init->header.height_px < 0)
	{
		int i = 0;
		int j = 0;
		for(i = 0; i < init->norm_height; i++)
		{
			for(j = 0; j < (int) init->header.width_px; j++)
			{
				fread(&init->pixels[i][j].blue, 1, 1, fp);
				fread(&init->pixels[i][j].green, 1, 1, fp);
				fread(&init->pixels[i][j].red, 1, 1, fp);
				fread(&init->pixels[i][j].alpha, 1, 1, fp);
			}
		}
	}
	else
	{
		int i = 0;
		int j = 0;
		for(i = init->norm_height - 1; i >= 0; i--)
		{
			for(j = 0; j < (int) init->header.width_px; j++)
			{
				fread(&init->pixels[i][j].blue, 1, 1, fp);
				fread(&init->pixels[i][j].green, 1, 1, fp);
				fread(&init->pixels[i][j].red, 1, 1, fp);
				fread(&init->pixels[i][j].alpha, 1, 1, fp);
			}
		}
	}
	return init;
}

void freeImage(BMPImage * image) {
	//1. Free each of the "rows" of the image->pixels
	for (int row = 0; row < image->norm_height; row++)
	{
		free(image->pixels[row]);
	}
	//2. Free the "spine" of the array
	free(image->pixels);
	//3. Free the "structure"
	free(image);
}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp) {
	//WRITE HEADER
	fwrite(&image->header.type, 2, 1, fp);
	fwrite(&image->header.size, 4, 1, fp);
	fwrite(&image->header.reserved1, 2, 1, fp);
	fwrite(&image->header.reserved2, 2, 1, fp);
	fwrite(&image->header.offset, 4, 1, fp);
	fwrite(&image->header.dib_header_size, 4, 1, fp);
	fwrite(&image->header.width_px, 4, 1, fp);
	fwrite(&image->header.height_px, 4, 1, fp);
	fwrite(&image->header.num_planes, 2, 1, fp);
	fwrite(&image->header.bits_per_pixel, 2, 1, fp);
	fwrite(&image->header.compression, 4, 1, fp);
	fwrite(&image->header.image_size_bytes, 4, 1, fp);
	fwrite(&image->header.x_resolution_ppm, 4, 1, fp);
	fwrite(&image->header.y_resolution_ppm, 4, 1, fp);
	fwrite(&image->header.num_colors, 4, 1, fp);
	fwrite(&image->header.important_colors, 4, 1, fp);
	//WRITE PIXELS
	int i = 0;
	int j = 0;
	if((int) image->header.height_px < 0)
	{
		for(i = 0; i < image->norm_height; i++)
		{
			for(j = 0; j < (int) image->header.width_px; j++)
			{
				fwrite(&image->pixels[i][j].blue, 1, 1, fp);
				fwrite(&image->pixels[i][j].green, 1, 1, fp);
				fwrite(&image->pixels[i][j].red, 1, 1, fp);
				fwrite(&image->pixels[i][j].alpha, 1, 1, fp);
			}
		}
	}
	else
	{
		for(i = image->norm_height - 1; i >= 0; i--)
		{
			for(j = 0; j < (int) image->header.width_px; j++)
			{
				fwrite(&image->pixels[i][j].blue, 1, 1, fp);
				fwrite(&image->pixels[i][j].green, 1, 1, fp);
				fwrite(&image->pixels[i][j].red, 1, 1, fp);
				fwrite(&image->pixels[i][j].alpha, 1, 1, fp);
			}
		}
	}
}
#endif
