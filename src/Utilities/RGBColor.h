#pragma once

#include <math.h>

class RGBColor {
	
public:
	
	// member variable
	double	r, g, b;
	
	// default constructor
	RGBColor();

	// greyscale constructor
	RGBColor(double c);

	// component constructor
	RGBColor(double _r, double _g, double _b);

	// copy constructor
	RGBColor(const RGBColor& c);
	
	// assignment operator
	RGBColor& operator= (const RGBColor& rhs); 

	// addition
	RGBColor operator+ (const RGBColor& c) const;

	// subtraction
	RGBColor operator- (const RGBColor& c) const;

	// in-place addition
	RGBColor& operator+= (const RGBColor& c);
	
	// multiplication by scalar
	RGBColor operator* (const double& a) const;
		
	// in-place multiplication by scalar
	RGBColor& operator*= (const double& a);					
	
	// division by scalar
	RGBColor operator/ (const double& a) const;
		
	// in-place division by scalar
	RGBColor& operator/= (const double& a); 
				
	// multiplication by color
	RGBColor operator* (const RGBColor& c) const;

	// in-place multiplication by color
	RGBColor& operator*= (const RGBColor& c);
		
	// equality check
	bool operator== (const RGBColor& c) const;	

	// inequality check
	bool operator!= (const RGBColor& c) const;

	// raise components to power of scalar
	RGBColor powc(const double& p) const;
		
	// the average of components
	double average() const;

	// the magnitude in color space
	double magnitude() const;

	// euclidean distance between colors in rgb space
	double difference(const RGBColor& rhs) const;

	// wavelength to RGB conversion
    static RGBColor convert_wave_length_nm_to_rgb(const double wave_length_nm);

	// normalize out of bounds colors (ratio preserved)
	RGBColor max_to_one() const;

	// set out of bounds colors to red
	RGBColor clamp_to_red() const;

	// raise components to power of gamma
	RGBColor gamma(double gamma) const;
};



// inlined functions:

inline RGBColor 
RGBColor::operator+ (const RGBColor& c) const 
{
	return RGBColor(this->r + c.r, this->g + c.g, this->b + c.b);
}

inline RGBColor
RGBColor::operator- (const RGBColor& c) const
{
	return RGBColor(this->r - c.r, this->g - c.g, this->b - c.b);
}

inline RGBColor& 
RGBColor::operator+= (const RGBColor& c) 
{
	this->r += c.r; this->g += c.g; this->b += c.b;
    return *this;
}

inline RGBColor 
RGBColor::operator* (const double& a) const 
{
	return RGBColor(this->r * a, this->g * a, this->b * a);	
}

inline RGBColor& 
RGBColor::operator*= (const double& a) 
{
	this->r *= a; this->g *= a; this->b *= a;
	return *this;
}

inline RGBColor 
RGBColor::operator/ (const double& a) const 
{
	return RGBColor (this->r / a, this->g / a, this->b / a);
}

inline RGBColor& 
RGBColor::operator/= (const double& a) 
{	
	double inv_a = 1.0 / a;
	this->r *= inv_a; this->g *= inv_a; this->b *= inv_a;
	return *this;
}

inline RGBColor 
RGBColor::operator* (const RGBColor& c) const 
{
	return RGBColor (this->r * c.r, this->g * c.g, this->b * c.b);
} 

inline RGBColor&
RGBColor::operator*= (const RGBColor& c) 
{
	this->r *= c.r; this->g *= c.g; this->b *= c.b;
	return *this;
}

inline bool
RGBColor::operator== (const RGBColor& c) const {
	return (this->r == c.r && this->g == c.g && this->b == c.b);
}

inline bool
RGBColor::operator!= (const RGBColor& c) const {
	return (this->r != c.r || this->g != c.g || this->b != c.b);
}

inline double											
RGBColor::average() const 
{
	return 0.333333333333 * (this->r + this->g + this->b);
}

inline double
RGBColor::magnitude() const
{
	return sqrt(r * r + g * g + b * b);
}

inline double 
RGBColor::difference(const RGBColor& rhs) const
{
	return sqrt((rhs.r - r) * (rhs.r - r)
		+ (rhs.g - g) * (rhs.g - g)
		+ (rhs.b - b) * (rhs.b - b));
}

RGBColor 
operator* (const double a, const RGBColor& c);

inline RGBColor 
operator* (const double a, const RGBColor& c) 
{
	return RGBColor (a * c.r, a * c.g, a * c.b);
}

inline RGBColor
RGBColor::convert_wave_length_nm_to_rgb(const double wave_length_nm) {
    // Credits: Dan Bruton http://www.physics.sfasu.edu/astro/color.html

    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;

    if ((380.0 <= wave_length_nm) && (wave_length_nm <= 439.0)) {
        red = -(wave_length_nm - 440.0) / (440.0 - 380.0);
        green = 0.0;
        blue = 1.0;
    }
    else if ((440.0 <= wave_length_nm) && (wave_length_nm <= 489.0)) {
        red = 0.0;
        green = (wave_length_nm - 440.0) / (490.0 - 440.0);
        blue = 1.0;
    }
    else if ((490.0 <= wave_length_nm) && (wave_length_nm <= 509.0)) {
        red = 0.0;
        green = 1.0;
        blue = -(wave_length_nm - 510.0) / (510.0 - 490.0);
    }
    else if ((510.0 <= wave_length_nm) && (wave_length_nm <= 579.0)) {
        red = (wave_length_nm - 510.0) / (580.0 - 510.0);
        green = 1.0;
        blue = 0.0;
    }
    else if ((580.0 <= wave_length_nm) && (wave_length_nm <= 644.0)) {
        red = 1.0;
        green = -(wave_length_nm - 645.0) / (645.0 - 580.0);
        blue = 0.0;
    }
    else if ((645.0 <= wave_length_nm) && (wave_length_nm <= 780.0)) {
        red = 1.0;
        green = 0.0;
        blue = 0.0;
    }

    double factor = 0.0;

    if ((380.0 <= wave_length_nm) && (wave_length_nm <= 419.0))
        factor = 0.3 + 0.7 * (wave_length_nm - 380.0) / (420.0 - 380.0);
    else if ((420.0 <= wave_length_nm) && (wave_length_nm <= 700.0))
        factor = 1.0;
    else if ((701.0 <= wave_length_nm) && (wave_length_nm <= 780.0))
        factor = 0.3 + 0.7 * (780.0 - wave_length_nm) / (780.0 - 700.0);
    else
        factor = 0.0;

	double r = red * factor;
	double g = green * factor;
	double b = blue * factor;

	return RGBColor(r, g, b);
}

inline RGBColor
RGBColor::max_to_one() const 
{
	double g_or_b = this->g > this->b ? this->g : this->b;
	double max_value = this->r > g_or_b ? this->r : g_or_b;

	return max_value > 1.0 ? RGBColor(*this / max_value) : RGBColor(*this);
}

inline RGBColor
RGBColor::clamp_to_red() const 
{
	if (this->r > 1.0 || this->g > 1.0 || this->b > 1.0)
		return RGBColor(1.0, 0.0, 0.0);
	else
		return *this;
}

inline RGBColor
RGBColor::gamma(double gamma) const 
{
	return this->powc(gamma);
}