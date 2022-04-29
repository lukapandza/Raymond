#include "FresnelReflector.h"

FresnelReflector::FresnelReflector()
	: BRDF(),
	ior_in(1.0),
	ior_out(1.0)
{}

FresnelReflector::FresnelReflector(const FresnelReflector& rhs)
	: BRDF(rhs),
	ior_in(rhs.ior_in),
	ior_out(rhs.ior_out)
{}

FresnelReflector*
FresnelReflector::clone() const
{
	return new FresnelReflector(*this);
}

FresnelReflector::~FresnelReflector()
{
	BRDF::~BRDF();
}

FresnelReflector&
FresnelReflector::operator=(const FresnelReflector& rhs)
{
	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);

	ior_in = rhs.ior_in; ior_out = rhs.ior_out;

	return *this;
}

RGBColor
FresnelReflector::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const
{
	return RGBColor(0, 0, 0);
}

RGBColor
FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const
{
	double n_dot_w_o = sr.normal * w_o;
	w_i = -w_o + sr.normal * (n_dot_w_o * 2.0);
	return RGBColor(1, 1, 1) * fresnel(sr) / fabs(sr.normal * w_i);
}

RGBColor 
FresnelReflector::rho(const ShadeRec& sr, const Vector3D& w_o) const
{
	return RGBColor(0, 0, 0);
}

double 
FresnelReflector::fresnel(const ShadeRec& sr) const
{
	Normal normal(sr.normal);
	double n_dot_d = -normal * sr.ray.d;

	double eta;
	if (n_dot_d < 0.0) {
		normal = -normal;
		eta = ior_out / ior_in;
	}
	else {
		eta = ior_in / ior_out;
	}

	double cos_theta_i = -normal * sr.ray.d;
	//double temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	double cos_theta_t = sqrt(1.0 - (1.0 - cos_theta_i * cos_theta_i)
		/ (eta * eta));
	double r_parallel = (eta * cos_theta_i - cos_theta_t)
		/ (eta * cos_theta_i + cos_theta_t);
	double r_perpendicular = (cos_theta_i - eta * cos_theta_t)
		/ (cos_theta_i + eta * cos_theta_t);
	double kr = 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);

	return kr;
}
