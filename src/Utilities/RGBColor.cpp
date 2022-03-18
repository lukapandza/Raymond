#include "RGBColor.h"
#include <math.h>

RGBColor::RGBColor()
	: r(0.0), g(0.0), b(0.0) 							
{}

RGBColor::RGBColor(double c)
	: r(c), g(c), b(c) 							
{}

RGBColor::RGBColor(double _r, double _g, double _b)	
	: r(_r), g(_g), b(_b)
{}

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{}

RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) 
{
	if (this == &rhs)
		return *this;

	this->r = rhs.r; this->g = rhs.g; this->b = rhs.b;

	return *this;
}

RGBColor
RGBColor::powc(const double& p) const 
{
	return RGBColor(pow(this->r, p), pow(this->g, p), pow(this->b, p));
}


