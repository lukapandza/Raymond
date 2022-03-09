#pragma once

#include "BRDF.h"

class PerfectSpecular : public BRDF {

public:

	PerfectSpecular(void); // default constructor

	PerfectSpecular(const PerfectSpecular& rhs); // copy constructor

	virtual PerfectSpecular*
		clone(void) const; // clone

	virtual
		~PerfectSpecular(); // destructor

	PerfectSpecular& //assignment operator
		operator= (const PerfectSpecular& rhs);

	// setters

	void
		set_kr(const double  c);

	void // set diffuse color
		set_cr(const double  c);

	void // set diffuse color
		set_cr(const double  r, const double  g, const double  b);

	void // set diffuse color
		set_cr(const RGBColor col);

	// functions

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	virtual RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double  pdf) const;

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& w_o) const;

private:

	double  kr;
	RGBColor cr;
};

// inlined functions:

inline void
PerfectSpecular::set_kr(const double  c) {
	kr = c;
}

inline void
PerfectSpecular::set_cr(const double  c) {
	cr = RGBColor(c, c, c);
}

inline void
PerfectSpecular::set_cr(const double  r, const double  g, const double  b) {
	cr = RGBColor(r, g, b);
}

inline void
PerfectSpecular::set_cr(const RGBColor col) {
	cr = col;
}