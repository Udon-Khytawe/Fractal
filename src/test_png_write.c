#include <stdlib.h>
#include <stdint.h>
#include "png_utils.h"

int main(int argc, char *argv[]){
	//init pixel map 
	size_t width = 1000;
	size_t height = 1000;
	rgb_t *pixel_map = (rgb_t*)malloc(sizeof(rgb_t)*width*height);

	double width_delta = 255.0/(width-1);
	double height_delta = 255.0/(height-1);
	for(size_t i = 0; i < height; ++i){
		uint8_t red = (uint8_t)(i*height_delta);
		for(size_t j = 0; j < width; ++j){
			uint8_t green = (uint8_t)(j*width_delta);
			pixel_map[i*width + j] = (rgb_t){red, green, 0};
		}
	}

	write_png(pixel_map, width, height, "example.png");
	free(pixel_map);
}
