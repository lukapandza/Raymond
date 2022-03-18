#pragma once

#include "BRDF.h"

class PerfectSpecular : public BRDF {

public:

	// default constructor
	PerfectSpecular(); 

	// copy constructor
	PerfectSpecular(const PerfectSpecular& rhs); 

	// clone
	PerfectSpecular* clone() const; 

	// destructor
	~PerfectSpecular(); 

	//assignment operator
	PerfectSpecular& operator= (const PerfectSpecular& rhs);

	// set reflection intensity
	void set_kr(const double  c);

	// set diffuse greyscale color
	void set_cr(const double  c);

	// set diffuse color
	void set_cr(const double  r, const double  g, const double  b);

	// set diffuse color
	void set_cr(const RGBColor col);

	RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double  pdf) const;

	RGBColor rho(const ShadeRec& sr, const Vector3D& w_o) const;

private:

	// reflection intensity
	double  kr;

	// reflection color
	RGBColor cr;
};

inline void
PerfectSpecular::set_kr(const double  c) 
{
	this->kr = c;
}

inline void
PerfectSpecular::set_cr(const double  c) 
{
	this->cr = RGBColor(c, c, c);
}

inline void
PerfectSpecular::set_cr(const double  r, const double  g, const double  b) 
{
	this->cr = RGBColor(r, g, b);
}

inline void
PerfectSpecular::set_cr(const RGBColor col) 
{
	this->cr = col;
}