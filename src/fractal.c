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
 * -p --palette list of colors to use 
 * -s --size width and height of the image to generate 
 * -n --iterations number of iterations 
 * -x --x-range min and max x values 
 * -y --y-range min and max y values 
 * -o --output filename 
 */

typedef struct{
	rgb_t left;
	rgb_t center;
	rgb_t right;
	char* path;
	size_t n;
	size_t width;
	size_t height;
	double min_x;
	double max_x;
	double min_y;
	double max_y;
} fractal_context;

int parse_arguments(fractal_context *context, int argc, char *argv[]);

int main(int argc, char *argv[]){
	//get the fractal context 
	fractal_context context;
	if(1 == parse_arguments(&context, argc, argv)){
		return 1;
	}

	//set up the color pallet
	rgb_t left = context.left;
	rgb_t center = context.center;
	rgb_t right = context.right;

	//get the command line input
	size_t n = context.n;
	size_t width = context.width;
	size_t height = context.height;

	//get the framing for the plot
	double min_x = context.min_x;
	double max_x = context.max_x;
	double min_y = context.min_y;
	double max_y = context.max_y;

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

	write_png(pixel_map, width, height, context.path);

	free(pixel_map);
}

/*
 * Command line options I want
 * -p --palette list of colors to use 
 * -s --size width and height of the image to generate 
 * -n --iterations number of iterations 
 * -x --x-range min and max x values 
 * -y --y-range min and max y values 
 * -o --output filename 
 * -l --list_colors print names of colors with ids
 */

void print_colors(){
	printf("White:  %d\n", WHITE);
	printf("Black:  %d\n", BLACK);
	printf("Red:    %d\n", RED);
	printf("Green:  %d\n", GREEN);
	printf("Blue:   %d\n", BLUE);
	printf("Purple: %d\n", PURPLE);
	printf("Yellow: %d\n", YELLOW);
	printf("Cyan:   %d\n", CYAN);
	printf("Orange: %d\n", ORANGE);
	printf("Pink:   %d\n", PINK);
}

int parse_arguments(fractal_context *context, int argc, char *argv[]){
	for(size_t i = 1; i < argc; ++i){
		switch(argv[i][1]){
			case 'p': context->left = get_color(strtoul(argv[i+1], NULL, 10)); context->center = get_color(strtoul(argv[i+2], NULL, 10)); context->right = get_color(strtoul(argv[i+3], NULL, 10)); i+=3; break;
			case 's': context->width = strtoul(argv[i+1], NULL, 10); context->height = strtoul(argv[i+2], NULL, 10); i+=2; break;
			case 'n': context->n = strtoul(argv[i+1], NULL, 10); ++i; break;
			case 'x': context->min_x = strtod(argv[i+1], NULL); context->max_x = strtod(argv[i+2], NULL); i+=2; break;
			case 'y': context->min_y = strtod(argv[i+1], NULL); context->max_y = strtod(argv[i+2], NULL); i+=2; break;
			case 'o': context->path = argv[1+i]; ++i; break;
			case 'l': print_colors(); return 1;
			default : fprintf(stderr, "Option not recognized\n"); return 1;
		}
	}
	return 0;
}
