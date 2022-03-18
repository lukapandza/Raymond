#pragma once

#include "BRDF.h"

class Lambertian : public BRDF {

public:

	// default constructor
	Lambertian(); 

	// copy constructor
	Lambertian(const Lambertian& rhs); 

	// clone
	virtual Lambertian* clone() const;

	// destructor
	virtual ~Lambertian(); 

	// assignment operator
	Lambertian& operator= (const Lambertian& rhs);

	// returns difusse intensity
	double get_kd();

	// set diffuse reflection coefficient
	void set_kd(const double  c); 

	// set diffuse color
	void set_cd(const double  c);

	// set diffuse color
	void set_cd(const double  r, const double  g, const double  b);

	// set diffuse color
	void set_cd(const RGBColor col);

	RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double & pdf) const;

	RGBColor rho(const ShadeRec& sr, const Vector3D& w_o) const;

private:

	// diffuse intensity
	double  kd; 

	// diffuse color
	RGBColor cd; 
};

inline void
Lambertian::set_kd(const double c) 
{
	this->kd = c;
}

inline void
Lambertian::set_cd(const double c) 
{
	this->cd = RGBColor(c);
}

inline void 
Lambertian::set_cd(const double r, const double g, const double b) 
{
	this->cd = RGBColor(r, g, b);
}

inline void
Lambertian::set_cd(const RGBColor col) 
{
	this->cd = col;
}

inline double
Lambertian::get_kd() 
{
	return this->kd;
}