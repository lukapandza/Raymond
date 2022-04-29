#pragma once

#include "../Samplers/Sampler.h"
#include "../Samplers/MultiJittered.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/RGBColor.h"

class BTDF {

public:

	// default constructor
	BTDF() {}

	// copy constructor
	BTDF(const BTDF& rhs) {}

	// clone
	virtual BTDF* clone() const = 0;

	// assignment operator
	BTDF& operator= (const BTDF& rhs) { return *this; }

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const = 0;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& w_o) const = 0;

	virtual bool tir(const ShadeRec& sr) const = 0;

};
