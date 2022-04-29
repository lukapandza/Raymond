#pragma once

#include "BTDF.h"

class FresnelTransmitter : public BTDF {

public:

	// default constructor
	FresnelTransmitter();

	// copy constructor
	FresnelTransmitter(const FresnelTransmitter& rhs);

	// clone
	FresnelTransmitter* clone() const;

	// assignment operator
	FresnelTransmitter& operator= (const FresnelTransmitter& rhs);

	void set_ior_in(const double s) { ior_in = s; }

	void set_ior_out(const double s) { ior_out = s; }

	RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	RGBColor rho(const ShadeRec& sr, const Vector3D& w_o) const;

	bool tir(const ShadeRec& sr) const;

	double fresnel(const ShadeRec& sr) const;

private:

	double ior_in, ior_out;
};