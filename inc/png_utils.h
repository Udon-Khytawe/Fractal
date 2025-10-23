#include <stdio.h>
#include <stddef.h>
#include <png.h>

#include "color.h"

#ifndef PNG_UTILS_H
#define PNG_UTILS_H

/*
 * Writes the pixel map the a png file
 * @param pixel_map the rgb pixel values to write
 * @param width the width of the png in pixels 
 * @param height the height of the png in pixels
 * @param path the path of the file to write
 * @return 0 on success 1 on failure
 */
int write_png(const rgb_t *pixel_map, const size_t width, const size_t height, const char *path);

#endif
