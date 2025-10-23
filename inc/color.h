#include <stdint.h>

#ifndef COLOR_H
#define COLOR_H

typedef struct{
	uint8_t r;//red value 
	uint8_t g;//green value 
	uint8_t b;//blue value  
} rgb_t;

enum color_name{
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	PURPLE,
	YELLOW,
	CYAN,
	ORANGE,
	PINK
};

/*
 * Returns the rgb value for a given color
 * @param color name from enum
 * @return rgb value 
 */
rgb_t get_color(const enum color_name color);

/*
 * Returns a linear blend between the left and right colors 
 * @param left the leftmost color in the colormap
 * @param right the rightmost color in the colormap
 * @param blend value between 0-1 determinting with 0 being the left color and 1 being right color
 * @return a linear blend between left and right 
 */
rgb_t bicolormap(const rgb_t left, const rgb_t right, const double blend);

/*
 * Returns a linear blend between the three colors 
 * @param left, leftmost color in the colormap
 * @param center, central color in the colormap
 * @param right, rightmost color in the colormap
 * @param blend value between 0-1 with 0 being the left color and 1 being the right color and 0.5 being the center color
 */
rgb_t tricolormap(const rgb_t left, const rgb_t center, const rgb_t right, const double blend);

#endif
