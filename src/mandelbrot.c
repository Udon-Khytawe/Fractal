#include "mandelbrot.h"

size_t mandelbrot_iterate(const double complex c, const size_t n){
	double complex z = 0;
	size_t i = 0; 
	//while i is less than the max iterations 
	//and the magnitude of z is less than 2
	while(i < n && cabs(z) < 2){
		z = z*z + c;
		++i;
	}

	return i;
}
