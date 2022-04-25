#pragma once

#include <stdlib.h>
#include <cstdint>
#include <math.h>
#include "Constants.h"
#include "RGBColor.h"

// find roots of second order polynomial
int solve_quadric(double c[3], double s[2]);

// find roots of third order polynomial
int solve_cubic(double c[4], double s[3]);

// fond roots of fourth order polynomial
int solve_quartic(double c[5], double s[4]);

// random int in [min_int, max_int]
inline int rand_int() 
{
	return rand();
}

// random double in [0.0, 1.0]
inline double rand_float() 
{
	return (double)rand_int() * invRAND_MAX;
}

// set seed for rand()
inline void set_rand_seed(const int seed) 
{
	srand(seed);
}

// random double in [low, high]
inline double rand_float(int low, double high) 
{
	return rand_float() * (high - low);
}

inline double rand_float(double low, double high)
{
    return low + rand_float() * (high - low);
}

// random int in [low, high]
inline int rand_int(int low, int high) 
{
	return (rand() % (high - low + 1)) + low;
}

// force scalar into range [min, max]
inline double clamp(const double num, const double min, const double max) 
{
	return num < min ? min : (num > max ? max : num);
}

// fast inverse square root
inline double fast_inv_sqrt(double num)
{
    double y = num;
    double x2 = y * .5;
    std::int64_t i = *(std::int64_t*)&y;
    // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double*)&i;
    y = y * (1.5 - (x2 * y * y));   // 1 iteration
    return y;
}