#pragma once

#include "BRDF.h"

class FresnelReflector : public BRDF {

public:

	// default constructor
	FresnelReflector();

	// copy constructor
	FresnelReflector(const FresnelReflector& rhs);

	// clone
	FresnelReflector* clone() const;

	// destructor
	~FresnelReflector();

	//assignment operator
	FresnelReflector& operator= (const FresnelReflector& rhs);

	void set_ior_in(const double s) { ior_in = s; }

	void set_ior_out(const double s) { ior_out = s; }

	RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	RGBColor rho(const ShadeRec& sr, const Vector3D& w_o) const;

	double fresnel(const ShadeRec& sr) const;

private:

	double ior_in, ior_out;
};