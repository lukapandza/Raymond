#pragma once

#include <stdlib.h>
#include "Constants.h"
#include "RGBColor.h"

int rand_int(void);

double rand_float(void);

void set_rand_seed(const int seed);

double rand_float(int low, double high);

int rand_int(int low, int high);

double clamp(const double num, const double min, const double max);

int solve_quadric(double c[3], double s[2]);

int solve_cubic(double c[4], double s[3]);

int solve_quartic(double c[5], double s[4]);


//inlined functions:

inline int rand_int() 
{
	return rand();
}

inline double rand_float() 
{
	return (double)rand_int() * invRAND_MAX;
}

inline void set_rand_seed(const int seed) 
{
	srand(seed);
}

inline double rand_float(int low, double high) 
{
	return rand_float() * (high - low);
}

inline int rand_int(int low, int high) 
{
	return (rand() % (high - low + 1)) + low;
}

inline double clamp(const double num, const double min, const double max) 
{
	return num < min ? min : (num > max ? max : num);
}