#pragma once

#include "BRDF.h"

class Lambertian : public BRDF {

public:

	Lambertian(void); // default constructor

	Lambertian(const Lambertian& rhs); // copy constructor

	virtual Lambertian*
		clone(void) const;

	virtual
		~Lambertian(); // destructor

	Lambertian& //assignment operator
		operator= (const Lambertian& rhs);

	double
		get_kd();

	// setters

	void // set diffuse reflection coefficient
		set_kd(const double  c); 

	void // set diffuse color
		set_cd(const double  c);

	void // set diffuse color
		set_cd(const double  r, const double  g, const double  b);

	void // set diffuse color
		set_cd(const RGBColor col);

	// functions

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, Vector3D& w_i, const Vector3D& w_o) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double & pdf) const;

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& w_o) const;

private:

	double  kd; // diffuse reflection coefficient
	RGBColor cd; // diffuse color
};

// inlined functions:

inline void
Lambertian::set_kd(const double  c) {
	kd = c;
}

inline void
Lambertian::set_cd(const double  c) {
	cd = RGBColor(c, c, c);
}

inline void 
Lambertian::set_cd(const double  r, const double  g, const double  b) {
	cd = RGBColor(r, g, b);
}

inline void
Lambertian::set_cd(const RGBColor col) {
	cd = col;
}

inline double
Lambertian::get_kd() {
	return this->kd;
}