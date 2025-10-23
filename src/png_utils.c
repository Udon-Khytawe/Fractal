#include "png_utils.h"

//https://www.libpng.org/pub/png/libpng-1.2.5-manual.html#section-4
int write_png(const rgb_t *pixel_map, const size_t width, const size_t height, const char *path){
	//open file for binary writing 
	FILE *f = fopen(path, "wb");
	if(NULL == f){
		return 1;
	}

	//create a png write struct
	//don't need to bother with error shenanigans hence the null values 
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(NULL == png_ptr){
		//close f 
		fclose(f);
		return 1;
	}

	//create a png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if(NULL == info_ptr){
		//close f 
		fclose(f);
		//free the png write struct 
		png_destroy_write_struct(&png_ptr, NULL);
		return 1;
	}

	//set up the long jumping for png errors
	if(setjmp(png_jmpbuf(png_ptr))){
		//close the file 
		fclose(f);
		//free the png structs 
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return 1;
	}

	//init the png io
	png_init_io(png_ptr, f);
	
	//write the IHDR
	//using 8 bit rgb with no interlacing 
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	//allocate space for row pointers
	png_byte **row_ptrs = png_malloc(png_ptr, height*sizeof(png_byte*));
	for(size_t i = 0; i < height; ++i){
		//allocate space for width
		row_ptrs[i] = png_malloc(png_ptr, sizeof(uint8_t)*width*3);
		//get ptr to row
		png_byte *row = row_ptrs[i];
		//for each pixel in the width
		for(size_t j = 0; j < width; ++j){
			//get the pixel 
			rgb_t pixel = pixel_map[i*width + j];
			//write the r g b values 
			row[0] = pixel.r;
			row[1] = pixel.g;
			row[2] = pixel.b;
			//increment by 3
			row+=3;
		}
	}

	//set the rows 
	png_set_rows(png_ptr, info_ptr, row_ptrs);
	//write the png
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	//close the file 
	fclose(f);
	//free the rows
	for(size_t i = 0; i < height; ++i){
		png_free(png_ptr, row_ptrs[i]);
	}
	//free the row pointers
	png_free(png_ptr, row_ptrs);
	//free the png structs 
	png_destroy_write_struct(&png_ptr, &info_ptr);

	return 0;
}
