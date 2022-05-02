#include "PerfectSpecular.h"

PerfectSpecular::PerfectSpecular() 
	: BRDF(),
	kr(1.0),
	cr(1.0)
{}

PerfectSpecular::PerfectSpecular(const PerfectSpecular& rhs) 
	: BRDF(rhs),
	kr(rhs.kr),
	cr(rhs.cr)
{}

PerfectSpecular*
PerfectSpecular::clone() const 
{
	return new PerfectSpecular(*this);
}

PerfectSpecular::~PerfectSpecular() 
{
	BRDF::~BRDF();
}

PerfectSpecular&
PerfectSpecular::operator= (const PerfectSpecular& rhs) 
{
	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);

	kr = rhs.kr; cr = rhs.cr;

	return *this;
}

RGBColor
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const 
{
	return black;
}

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const 
{
	//double n_dot_wo = sr.normal * w_o;
	//w_i = -w_o + 2.0 * sr.normal * n_dot_wo;
	w_i = -w_o + 2.0 * (sr.normal * w_o) * sr.normal;

	//return (kr * cr / (sr.normal * w_i));
	return kr * cr;
}

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double  pdf) const 
{
	w_i = -w_o + 2.0 * (sr.normal * w_o) * sr.normal;
	pdf = sr.normal * w_i;

	return kr * cr;
}

RGBColor
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& w_o) const 
{
	return black;
}
