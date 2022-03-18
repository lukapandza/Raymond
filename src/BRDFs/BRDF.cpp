#include "BRDF.h"
#include "../Utilities/Constants.h"

BRDF::BRDF() 
	: sampler_ptr(nullptr)
{}

BRDF::BRDF(const BRDF& rhs)
	: sampler_ptr(rhs.sampler_ptr)
{
	if (rhs.sampler_ptr)
		this->sampler_ptr = rhs.sampler_ptr->clone();
	else
		this->sampler_ptr = nullptr;
}

BRDF::~BRDF() 
{
	if (sampler_ptr)
		delete sampler_ptr;
}

BRDF&
BRDF::operator= (const BRDF& rhs) 
{
	if (this == &rhs)
		return *this;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	return *this;
}

RGBColor
BRDF::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const 
{
	return black;
}

RGBColor
BRDF::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const 
{
	return black;
}

RGBColor
BRDF::rho(const ShadeRec& sr, const Vector3D& w_o) const 
{
	return black;
}
