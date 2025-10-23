#include "color.h"

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
