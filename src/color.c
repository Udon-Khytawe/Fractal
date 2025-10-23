#include "color.h"

rgb_t get_color(const enum color_name color){
	switch(color){
		case WHITE:  return (rgb_t){255,255,255};
		case BLUE:   return (rgb_t){0,0,255};
		case RED:    return (rgb_t){255,0,0};
		case GREEN:  return (rgb_t){0,255,0};
		case PURPLE: return (rgb_t){255,0,255};
		case YELLOW: return (rgb_t){255,255,0};
		case CYAN:   return (rgb_t){0,255,255};
		case ORANGE: return (rgb_t){255, 128, 0};
		case PINK:   return (rgb_t){255,100,168};
		default:     return (rgb_t){0,0,0};//black is default 
	}
}

rgb_t bicolormap(const rgb_t left, const rgb_t right, const double blend){
	rgb_t out;
	out.r = (uint8_t)(left.r*(1-blend) + right.r*blend);
	out.g = (uint8_t)(left.g*(1-blend) + right.g*blend);
	out.b = (uint8_t)(left.b*(1-blend) + right.b*blend);

	return out;
}

rgb_t tricolormap(const rgb_t left, const rgb_t center, const rgb_t right, const double blend){
	if(blend < 0.5){
		return bicolormap(left, center, blend*2);
	}
	return bicolormap(center, right, blend*2 - 1);
}
