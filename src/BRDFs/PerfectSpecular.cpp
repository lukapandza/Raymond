#include "PerfectSpecular.h"

PerfectSpecular::PerfectSpecular(void) 
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
PerfectSpecular::clone(void) const {
	return new PerfectSpecular(*this);
}

PerfectSpecular::~PerfectSpecular(void) {
	BRDF::~BRDF();
}

PerfectSpecular&
PerfectSpecular::operator= (const PerfectSpecular& rhs) {

	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);

	kr = rhs.kr;
	cr = rhs.cr;

	return *this;
}

RGBColor
PerfectSpecular::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const {
	return black;
}

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const {
	
	double n_dot_wo = sr.normal * w_o;
	w_i = -w_o + 2.0 * sr.normal * n_dot_wo;

	return (kr * cr / (sr.normal * w_i));
}

RGBColor
PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double  pdf) const {
	
	double  n_dot_wo = sr.normal * w_o;
	w_i = -w_o + 2.0 * sr.normal * n_dot_wo;
	pdf = sr.normal * w_i;

	return kr * cr;
}


RGBColor
PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& w_o) const {
	return black;
}

