#pragma once

#include <stdlib.h>
#include "RGBColor.h"

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 1.0E-6; 
const double	kHugeValue	= 1.0E10;

const RGBColor	black(0.0);
const RGBColor	white(1.0);
const RGBColor	red(1.0, 0.0, 0.0);

const double 	invRAND_MAX = 1.0 / (double)RAND_MAX;
