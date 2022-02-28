#include "Reflective.h"
#include "../World/World.h"

Reflective::Reflective(void)
	: Phong(),
	reflective_brdf(new PerfectSpecular)
{}

Reflective::Reflective(const Reflective& rhs) 
	: Phong(rhs) {
	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();
	else
		reflective_brdf = NULL;
}

Reflective*
Reflective::clone(void) const {
	return new Reflective(*this);
}

Reflective::~Reflective(void) {
	
	Phong::~Phong();

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}

Reflective&
Reflective::operator=(const Reflective& rhs) {
	
	if (this == &rhs)
		return *this;

	Phong::operator=(rhs);

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return *this;
}

RGBColor
Reflective::shade(ShadeRec& sr) {

	RGBColor L(Phong::shade(sr)); // direct illumination
	Vector3D w_o = -sr.ray.d;
	Vector3D w_i;

	RGBColor fr = reflective_brdf->sample_f(sr, w_i, w_o);
	Ray reflected_ray(sr.hit_point, w_i);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i);

	return L;
}

RGBColor
Reflective::area_light_shade(ShadeRec& sr) {
	
	RGBColor L(Phong::area_light_shade(sr));
	Vector3D w_o = -sr.ray.d;
	Vector3D w_i;

	RGBColor fr = reflective_brdf->sample_f(sr, w_i, w_o);
	Ray reflected_ray(sr.hit_point, w_i);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i);

	return L;
}

RGBColor
Reflective::path_shade(ShadeRec& sr) {
	
	Vector3D w_o = -sr.ray.d;
	Vector3D w_i;
	double  pdf = 0;
	RGBColor fr = reflective_brdf->sample_f(sr, w_o, w_i, pdf);

	Ray reflected_ray(sr.hit_point, w_i);

	return fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i) / pdf;
}

RGBColor
Reflective::global_shade(ShadeRec& sr) {

	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}