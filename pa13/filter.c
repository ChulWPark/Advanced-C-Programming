#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

#ifndef BLUR_OFF
BMPImage * blur(BMPImage * image){
	BMPImage * blurimage = malloc(sizeof(BMPImage));
	blurimage->header.type = image->header.type;
	blurimage->header.size = image->header.size;
	blurimage->header.reserved1 = image->header.reserved1;
	blurimage->header.reserved2 = image->header.reserved2;
	blurimage->header.offset = image->header.offset;
	blurimage->header.dib_header_size = image->header.dib_header_size;
	blurimage->header.width_px = image->header.width_px;
	blurimage->header.height_px = image->header.height_px;
	blurimage->header.num_planes = image->header.num_planes;
	blurimage->header.bits_per_pixel = image->header.bits_per_pixel;
	blurimage->header.compression = image->header.compression;
	blurimage->header.image_size_bytes = image->header.image_size_bytes;
	blurimage->header.x_resolution_ppm = image->header.x_resolution_ppm;
	blurimage->header.y_resolution_ppm = image->header.y_resolution_ppm;
	blurimage->header.num_colors = image->header.num_colors;
	blurimage->header.important_colors = image->header.important_colors;
	if((int)blurimage->header.height_px < 0)
	{
		blurimage->norm_height = (int)blurimage->header.height_px * -1;
	}
	else
	{
		blurimage->norm_height = (int) blurimage->header.height_px;
	}
	blurimage->pixels = malloc(blurimage->norm_height * sizeof(Pixel *));
	int row;
	for(row = 0; row < blurimage->norm_height; row++)
	{
		blurimage->pixels[row] = malloc( (int)blurimage->header.width_px * sizeof(Pixel));
	}
	int i = 0;
	int j = 0;
	Pixel fa;
	Pixel fb;
	Pixel fc;
	Pixel fd;
	Pixel fe;
	Pixel ff;
	Pixel fg;
	Pixel fh;
	Pixel fi;
	for(i = 0; i < blurimage->norm_height; i++)
	{
		for(j = 0; j < (int) blurimage->header.width_px; j++)
		{
			//LEFT TOP CORNER
			if( (i - 1) < 0 && (j - 1) < 0 )
			{
				fa = image->pixels[i][j];
				fb = image->pixels[i][j];
				fc = image->pixels[i][j+1];
				fd = image->pixels[i][j];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			//RIGHT TOP CORNER
			else if( (i - 1) < 0 && (j + 1) == (int) blurimage->header.width_px )
			{	
				fa = image->pixels[i][j-1];
				fb = image->pixels[i][j];
				fc = image->pixels[i][j];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j];
			}
			//LEFT BOTTOM CORNER
			else if( (i + 1) == blurimage->norm_height && (j - 1) < 0 )
			{
				fa = image->pixels[i-1][j];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i][j];
				fh = image->pixels[i][j];
				fi = image->pixels[i][j+1];
			}
			//RIGHT BOTTOM CORNER
			else if( (i + 1) == blurimage->norm_height && (j + 1) == (int) blurimage->header.width_px )
			{	
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j];
				fg = image->pixels[i][j-1];
				fh = image->pixels[i][j];
				fi = image->pixels[i][j];
			}
			//TOP
			else if( (i - 1) < 0 )
			{
				fa = image->pixels[i][j-1];
				fb = image->pixels[i][j];
				fc = image->pixels[i][j+1];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			//LEFT
			else if( (j - 1) < 0 )
			{
				fa = image->pixels[i-1][j];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			//RIGHT
			else if( (j + 1) == (int) blurimage->header.width_px )
			{
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j];
			}
			//BOTTOM
			else if( (i + 1) == blurimage->norm_height )
			{
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i][j-1];
				fh = image->pixels[i][j];
				fi = image->pixels[i][j+1];
			}
			//BASE CASE
			else
			{
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			///////////
			int blue = ((int)fa.blue + (int)fb.blue + (int)fc.blue + (int)fd.blue + (int)fe.blue + (int)ff.blue + (int)fg.blue + (int)fh.blue + (int)fi.blue) / 9;
			if(blue > 255)
			{
				blurimage->pixels[i][j].blue = 255;
			}
			else if(blue < 0)
			{
				blurimage->pixels[i][j].blue = 0;
			}
			else
			{
				blurimage->pixels[i][j].blue = blue;
			}
			int green = ((int)fa.green + (int)fb.green + (int)fc.green + (int)fd.green + (int)fe.green + (int)ff.green + (int)fg.green + (int)fh.green + (int)fi.green) / 9;
			if(green > 255)
			{
				blurimage->pixels[i][j].green = 255;
			}
			else if(green < 0)
			{
				blurimage->pixels[i][j].green = 0;
			}
			else
			{
				blurimage->pixels[i][j].green = green;
			}
			int red = ((int)fa.red + (int)fb.red + (int)fc.red + (int)fd.red + (int)fe.red + (int)ff.red + (int)fg.red + (int)fh.red + (int)fi.red) / 9;
			if(red > 255)
			{
				blurimage->pixels[i][j].red = 255;
			}
			else if(red < 0)
			{
				blurimage->pixels[i][j].red = 0;
			}
			else
			{
				blurimage->pixels[i][j].red = red;
			}
			int alpha = ((int)fa.alpha + (int)fb.alpha + (int)fc.alpha + (int)fd.alpha + (int)fe.alpha + (int)ff.alpha + (int)fg.alpha + (int)fh.alpha + (int)fi.alpha) / 9;
			if(alpha > 255)
			{
				blurimage->pixels[i][j].alpha = 255;
			}
			else if(alpha < 0)
			{
				blurimage->pixels[i][j].alpha = 0;
			}
			else
			{
				blurimage->pixels[i][j].alpha = alpha;
			}
		}
	}
	return blurimage;
}
#endif

// EXTRA CREDIT START
BMPImage * apply(BMPImage * image, BoxFilter f) {
	BMPImage * appim = malloc(sizeof(BMPImage));
	appim->header.type = image->header.type;
	appim->header.size = image->header.size;
	appim->header.reserved1 = image->header.reserved1;
	appim->header.reserved2 = image->header.reserved2;
	appim->header.offset = image->header.offset;
	appim->header.dib_header_size = image->header.dib_header_size;
	appim->header.width_px = image->header.width_px;
	appim->header.height_px = image->header.height_px;
	appim->header.num_planes = image->header.num_planes;
	appim->header.bits_per_pixel = image->header.bits_per_pixel;
	appim->header.compression = image->header.compression;
	appim->header.image_size_bytes = image->header.image_size_bytes;
	appim->header.x_resolution_ppm = image->header.x_resolution_ppm;
	appim->header.y_resolution_ppm = image->header.y_resolution_ppm;
	appim->header.num_colors = image->header.num_colors;
	appim->header.important_colors = image->header.important_colors;
	if(appim->header.height_px < 0)
	{
		appim->norm_height = (int) (appim->header.height_px * -1);
	}
	else
	{
		appim->norm_height = (int) appim->header.height_px;
	}
	appim->pixels = malloc(appim->norm_height * sizeof(Pixel *));
	int row;
	for(row = 0; row < appim->norm_height; row++)
	{
		appim->pixels[row] = malloc( (int)appim->header.width_px * sizeof(Pixel));
	}
	int i = 0;
	int j = 0;
	Pixel fa;
	Pixel fb;
	Pixel fc;
	Pixel fd;
	Pixel fe;
	Pixel ff;
	Pixel fg;
	Pixel fh;
	Pixel fi;
	for(i = 0; i < appim->norm_height; i++)
	{
		for(j = 0; j < (int) appim->header.width_px; j++)
		{
			//LEFT TOP CORNER
			if( (i - 1) < 0 && (j - 1) < 0 )
			{
				fa = image->pixels[i][j];
				fb = image->pixels[i][j];
				fc = image->pixels[i][j+1];
				fd = image->pixels[i][j];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			//RIGHT TOP CORNER
			else if( (i - 1) < 0 && (j + 1) == (int) appim->header.width_px )
			{	
				fa = image->pixels[i][j-1];
				fb = image->pixels[i][j];
				fc = image->pixels[i][j];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j];
			}
			//LEFT BOTTOM CORNER
			else if( (i + 1) == appim->norm_height && (j - 1) < 0 )
			{
				fa = image->pixels[i-1][j];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i][j];
				fh = image->pixels[i][j];
				fi = image->pixels[i][j+1];
			}
			//RIGHT BOTTOM CORNER
			else if( (i + 1) == appim->norm_height && (j + 1) == (int) appim->header.width_px )
			{	
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j];
				fg = image->pixels[i][j-1];
				fh = image->pixels[i][j];
				fi = image->pixels[i][j];
			}
			//TOP
			else if( (i - 1) < 0 )
			{
				fa = image->pixels[i][j-1];
				fb = image->pixels[i][j];
				fc = image->pixels[i][j+1];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			//LEFT
			else if( (j - 1) < 0 )
			{
				fa = image->pixels[i-1][j];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			//RIGHT
			else if( (j + 1) == (int) appim->header.width_px )
			{
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j];
			}
			//BOTTOM
			else if( (i + 1) == appim->norm_height )
			{
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i][j-1];
				fh = image->pixels[i][j];
				fi = image->pixels[i][j+1];
			}
			//BASE CASE
			else
			{
				fa = image->pixels[i-1][j-1];
				fb = image->pixels[i-1][j];
				fc = image->pixels[i-1][j+1];
				fd = image->pixels[i][j-1];
				fe = image->pixels[i][j];
				ff = image->pixels[i][j+1];
				fg = image->pixels[i+1][j-1];
				fh = image->pixels[i+1][j];
				fi = image->pixels[i+1][j+1];
			}
			///////////
			int blue = ( (int)fa.blue * f.filter[0][0] + (int)fb.blue * f.filter[0][1] + (int)fc.blue * f.filter[0][2] + (int)fd.blue * f.filter[1][0] + (int)fe.blue * f.filter[1][1] + (int)ff.blue * f.filter[1][2] + (int)fg.blue * f.filter[2][0] + (int)fh.blue * f.filter[2][1] + (int)fi.blue * f.filter[2][2]) / f.norm;
			if(blue > 255)
			{
				appim->pixels[i][j].blue = 255;
			}
			else if(blue < 0)
			{
				appim->pixels[i][j].blue = 0;
			}
			else
			{
				appim->pixels[i][j].blue = blue;
			}
			int green = ((int)fa.green * f.filter[0][0] + (int)fb.green * f.filter[0][1] + (int)fc.green * f.filter[0][2] + (int)fd.green * f.filter[1][0] + (int)fe.green * f.filter[1][1] + (int)ff.green * f.filter[1][2] + (int)fg.green * f.filter[2][0] + (int)fh.green * f.filter[2][1] + (int)fi.green * f.filter[2][2]) / f.norm;
			if(green > 255)
			{
				appim->pixels[i][j].green = 255;
			}
			else if(green < 0)
			{
				appim->pixels[i][j].green = 0;
			}
			else
			{
				appim->pixels[i][j].green = green;
			}
			int red = ((int)fa.red * f.filter[0][0] + (int)fb.red * f.filter[0][1] + (int)fc.red * f.filter[0][2] + (int)fd.red * f.filter[1][0] + (int)fe.red * f.filter[1][1] + (int)ff.red * f.filter[1][2] + (int)fg.red * f.filter[2][0] + (int)fh.red * f.filter[2][1] + (int)fi.red * f.filter[2][2]) / f.norm;
			if(red > 255)
			{
				appim->pixels[i][j].red = 255;
			}
			else if(red < 0)
			{
				appim->pixels[i][j].red = 0;
			}
			else
			{
				appim->pixels[i][j].red = red;
			}
			int alpha = ((int)fa.alpha * f.filter[0][0] + (int)fb.alpha * f.filter[0][1] + (int)fc.alpha * f.filter[0][2] + (int)fd.alpha * f.filter[1][0] + (int)fe.alpha * f.filter[1][1] + (int)ff.alpha * f.filter[1][2] + (int)fg.alpha * f.filter[2][0] + (int)fh.alpha * f.filter[2][1] + (int)fi.alpha * f.filter[2][2]) / f.norm;
			if(alpha > 255)
			{
				appim->pixels[i][j].alpha = 255;
			}
			else if(alpha < 0)
			{
				appim->pixels[i][j].alpha = 0;
			}
			else
			{
				appim->pixels[i][j].alpha = alpha;
			}
		}
	}
	return appim;
}

BoxFilter * readFilter(FILE * infile) {
	char first[30] = {0};
	char second[30] = {0};
	char third[30] = {0};
	char factor[30] = {0};
	char temp[30] = {0};
	fgets(first, 30, infile); 
	fgets(second, 30, infile);
	fgets(third, 30, infile);
	fgets(factor, 30, infile);
	
	BoxFilter * filt = malloc(sizeof(BoxFilter));
	
	int i = 0;
	int j = 0;
	int count = 0;
	while(first[i] != '\0')
	{
		if(first[i] == ' ')
		{
			temp[j] = '\0';
			filt->filter[0][count] = (int) atof(temp);
			count++;
			i++;
			j = 0;
		}
		else
		{
			temp[j] = first[i];
			j++;
			i++;
		}
	}
	temp[j] = '\0';
	filt->filter[0][count] = (int) atof(temp);
	i = 0;
	j = 0;
	count = 0;
	while(second[i] != '\0')
	{
		if(second[i] == ' ')
		{
			temp[j] = '\0';
			filt->filter[1][count] = (int) atof(temp);
			count++;
			i++;
			j = 0;
		}
		else
		{
			temp[j] = second[i];
			j++;
			i++;
		}
	}
	temp[j] = '\0';
	filt->filter[1][count] = (int) atof(temp);
	i = 0;
	j = 0;
	count = 0;
	while(third[i] != '\0')
	{
		if(third[i] == ' ')
		{
			temp[j] = '\0';
			filt->filter[2][count] = (int) atof(temp);
			count++;
			i++;
			j = 0;
		}
		else
		{
			temp[j] = third[i];
			j++;
			i++;
		}
	}
	temp[j] = '\0';
	filt->filter[2][count] = (int) atof(temp);
	i = 0;
	j = 0;
	while(factor[i] != '\0')
	{
		temp[j] = factor[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	filt->norm = atof(temp);

	return filt;

}
// EXTRA CREDIT END
