#include <complex.h>
#include <stddef.h>

#ifndef MANDELBROT_H
#define MANDELBROT_H

/*
 * Returns the number of iterations before |z_k| > 2 for z_k = z_{k-1}^2 + c
 * @param c parameter for z^2 + c
 * @param n the max number of iterations 
 * @return the number of iterations before |z| > 2 or n
 */
size_t mandelbrot_iterate(const double complex c, const size_t n);

#endif
