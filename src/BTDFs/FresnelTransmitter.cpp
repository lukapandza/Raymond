#include "FresnelTransmitter.h"

FresnelTransmitter::FresnelTransmitter()
	: ior_in(1.0),
	ior_out(1.0)
{}

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& rhs) 
	: ior_in(rhs.ior_in),
	ior_out(rhs.ior_out)
{}

FresnelTransmitter*
FresnelTransmitter::clone() const
{
	return new FresnelTransmitter(*this);
}

FresnelTransmitter&
FresnelTransmitter::operator= (const FresnelTransmitter& rhs)
{
	if (this == &rhs)
		return *this;

	ior_in = rhs.ior_in;
	ior_out = rhs.ior_out;

	return *this;
}

RGBColor 
FresnelTransmitter::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const
{
	return RGBColor(0, 0, 0);
}

bool
FresnelTransmitter::tir(const ShadeRec& sr) const
{
	double n_dot_d = -sr.normal * sr.ray.d;
	double cos_theta_i = sr.normal * -sr.ray.d;
	double eta = n_dot_d < 0.0 ? ior_out / ior_in : ior_in / ior_out;

	return (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta)) < 0.0;
}

RGBColor 
FresnelTransmitter::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const
{
	Normal n(sr.normal);
	double cos_theta_i = n * w_o;
	double eta = ior_in / ior_out;

	if (cos_theta_i < 0.0) {
		cos_theta_i = -cos_theta_i;
		n = -n;
		eta = 1.0 / eta;
	}

	double temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	double cos_theta_2 = sqrt(temp);

	w_i = (-w_o / eta) - Vector3D(n) * (cos_theta_2 - cos_theta_i / eta);

	double kte = fresnel(sr) / (eta * eta);
	return RGBColor(1, 1, 1) * kte / fabs(sr.normal * w_i);
}

RGBColor 
FresnelTransmitter::rho(const ShadeRec& sr, const Vector3D& w_o) const
{
	return RGBColor(0, 0, 0);
}

double
FresnelTransmitter::fresnel(const ShadeRec& sr) const
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

	return 1.0 - kr;
}
