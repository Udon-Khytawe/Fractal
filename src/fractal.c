#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <complex.h>
#include <omp.h>

#include "png_utils.h"
#include "mandelbrot.h"
#include "color.h"

/*
 * Command line options I want
 * -l --left for leftmost color
 * -r --right for rightmost color
 * -c --center for center color 
 * -s --size width and height of the image to generate 
 * -n --iterations number of iterations 
 * -xr --x-range min and max x values 
 * -yr --y-range min and max y values 
 */

typedef struct{
	rgb_t left;
	rgb_t center;
	rgb_t right;
	size_t n;
	size_t width;
	size_t height;
	double min_x;
	double max_x;
	double min_y;
	double max_x;
} fractal_context;

int main(int argc, char *argv[]){
	//set up the color pallet
	rgb_t left = (rgb_t){255,255,255};
	rgb_t center = (rgb_t){0,0,0};
	rgb_t right = (rgb_t){255,255,255};

	//get the command line input
	size_t n = strtoul(argv[1], NULL, 10);
	size_t width = strtoul(argv[2], NULL, 10);
	size_t height = strtoul(argv[3], NULL, 10);

	//get the framing for the plot
	double min_x = -2;
	double max_x = 1;
	double min_y = -1;
	double max_y = 1;

	//get the spacing between points 
	double x_delta = (max_x - min_x)/(width-1);
	double y_delta = (max_y - min_y)/(height-1);

	//allocate memory for the pixel map
	rgb_t *pixel_map = (rgb_t*)malloc(sizeof(rgb_t)*width*height);

	#pragma omp parallel for
	for(size_t i = 0; i < height; ++i){
		double y_offset = max_y - i*y_delta;
		for(size_t j = 0; j < width; ++j){
			double x_offset = min_x + j*x_delta;
			size_t iterations = mandelbrot_iterate(x_offset + I*y_offset, n);
			pixel_map[i*width + j] = tricolormap(left, center, right, ((double)iterations) / n);
		}
	}

	write_png(pixel_map, width, height, "mandelbrot.png");

	free(pixel_map);
}
