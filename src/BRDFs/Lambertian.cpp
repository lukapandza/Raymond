#include "Lambertian.h"

Lambertian::Lambertian(void) 
	: BRDF(),
	kd(1.0),
	cd(1.0)
{}

Lambertian::Lambertian(const Lambertian& rhs) 
	: BRDF(rhs),
	kd(rhs.kd),
	cd(rhs.cd)
{}

Lambertian*
Lambertian::clone() const 
{
	return new Lambertian(*this);
}

Lambertian::~Lambertian() 
{
	BRDF::~BRDF();
}

Lambertian&
Lambertian::operator=(const Lambertian& rhs) 
{
	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);

	kd = rhs.kd;
	cd = rhs.cd;

	return *this;
}

RGBColor
Lambertian::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const 
{
	return kd * cd * invPI;
}

RGBColor
Lambertian::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const 
{
	Vector3D w(sr.normal);
	Vector3D v = Vector3D(0.0034, 1.0, 0.0063) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = this->sampler_ptr->sample_hemisphere();
	w_i = sp.x * u + sp.y * v + sp.z * w;
	w_i.normalize();

	return this->kd * this->cd;
}

RGBColor
Lambertian::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double & pdf) const 
{
	Vector3D w(sr.normal);
	Vector3D v = Vector3D(0.0034, 1.0, 0.0063) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	w_i = sp.x * u + sp.y * v + sp.z * w;
	w_i.normalize();
	pdf = (sr.normal * w_i) * invPI;

	return kd * cd * invPI;
}

RGBColor
Lambertian::rho(const ShadeRec& sr, const Vector3D& w_o) const 
{
	return kd * cd;
}
