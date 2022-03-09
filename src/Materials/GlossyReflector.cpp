#include "GlossyReflector.h"
#include "../World/World.h"

GlossyReflector::GlossyReflector(void)
	: Phong2(),
	glossy_specular_brdf(new GlossySpecular)
{}

GlossyReflector::GlossyReflector(const GlossyReflector& rhs)
	: Phong2(rhs) {
	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = rhs.glossy_specular_brdf->clone();
	else
		glossy_specular_brdf = NULL;
}

GlossyReflector*
GlossyReflector::clone(void) const {
	return new GlossyReflector(*this);
}

GlossyReflector::~GlossyReflector(void) {

	Phong2::~Phong2();

	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
}

GlossyReflector&
GlossyReflector::operator=(const GlossyReflector& rhs) {

	if (this == &rhs)
		return *this;

	Phong2::operator=(rhs);

	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}

	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = rhs.glossy_specular_brdf->clone();

	return *this;
}

RGBColor
GlossyReflector::area_light_shade(ShadeRec& sr) {
	
	RGBColor L(Phong2::area_light_shade(sr)); // direct illumination
	
	Vector3D w_o(-sr.ray.d);
	Vector3D w_i;
	double  pdf;

	RGBColor fr(glossy_specular_brdf->sample_f(sr, w_o, w_i, pdf));
	Ray reflected_ray(sr.hit_point, w_i);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i) / pdf;

	return L;
}

RGBColor
GlossyReflector::path_shade(ShadeRec& sr) {

	
	RGBColor L(Phong2::path_shade(sr)); // direct illumination

	Vector3D w_o(-sr.ray.d);
	Vector3D w_i;
	double pdf;
	
	L += glossy_specular_brdf->sample_f(sr, w_o, w_i, pdf)
		* sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1)
		* (sr.normal * w_i)
		/ pdf;
	
	return L;

	/*
	Vector3D w_o(-sr.ray.d);

	Vector3D w_i_p;
	double pdf_p;
	RGBColor f_p = this->brdf->sample_f(sr, w_o, w_i_p, pdf_p);

	Vector3D w_i_r;
	double pdf_r;
	RGBColor f_r = this->glossy_specular_brdf->sample_f(sr, w_o, w_i_r, pdf_r);

	double p_phong = (this->get_kd() + this->get_ks()) / (this->get_kd() + this->get_ks() + this->glossy_specular_brdf->get_ks());
	double p_reflect = this->glossy_specular_brdf->get_ks() / (this->get_kd() + this->get_ks() + this->glossy_specular_brdf->get_ks());
	double rand = rand_float(0, 1.0);

	double pdf = (1.0 - rand) * pdf_p
		+ rand * pdf_r;

	if (rand < p_phong)
		return f_p
			* sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_p), sr.depth + 1)
			* (sr.normal * w_i_p)
			/ pdf;

	else
		return f_r
			* sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_r), sr.depth + 1)
			* (sr.normal * w_i_r)
			/ pdf
	*/
}

RGBColor
GlossyReflector::global_shade(ShadeRec& sr) {

	RGBColor L(0);

	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);
	return L + f;
}
