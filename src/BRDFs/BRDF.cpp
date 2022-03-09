#include "BRDF.h"
#include "../Utilities/Constants.h"

// default constructor
BRDF::BRDF(void) 
	: sampler_ptr(NULL)
{}

// copy constructor
BRDF::BRDF(const BRDF& rhs)
	: sampler_ptr(rhs.sampler_ptr)
{
	if (rhs.sampler_ptr)
		this->sampler_ptr = rhs.sampler_ptr->clone();
	else
		this->sampler_ptr = nullptr;
}

// destructor
BRDF::~BRDF() {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

// assignment operator
BRDF&
BRDF::operator= (const BRDF& rhs) {
	
	if (this == &rhs)
		return *this;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return *this;
}

RGBColor
BRDF::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const {
	return black;
}

RGBColor
BRDF::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const {
	return black;
}

RGBColor
BRDF::rho(const ShadeRec& sr, const Vector3D& w_o) const {
	return black;
}
