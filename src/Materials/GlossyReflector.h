#pragma once

#include "Material.h"
#include "BRDFs/Lambertian.h"
#include "BRDFs/GlossySpecular.h"

class GlossyReflector : public Material {

public:

	GlossyReflector();

	GlossyReflector(const GlossyReflector& rhs);

	GlossyReflector*
		clone() const;

	~GlossyReflector();

	GlossyReflector&
		operator=(const GlossyReflector& rhs);

	void
		set_samples(const int num_samples);

	void
		set_ka(const double k);

	void
		set_ca(const double r, const double g, const double b);


	void 
		set_kd(const double k);

	void
		set_cd(const double r, const double g, const double b);

	void
		set_ks(const double k);

	void
		set_cs(const double r, const double g, const double b);

	void
		set_exp_s(const double e);

	void
		set_kr(const double  k);

	void
		set_cr(const double  r, const double  g, const double  b);

	void
		set_exp_r(const double e);

	RGBColor
		area_light_shade(ShadeRec& sr);

	RGBColor
		path_shade(ShadeRec& sr);

	RGBColor
		global_shade(ShadeRec& sr);

private:

	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
	GlossySpecular* reflected_brdf;
};

inline void
GlossyReflector::set_samples(const int num_samples) {
	this->diffuse_brdf->set_samples(num_samples);
	this->specular_brdf->set_samples(num_samples);
	this->reflected_brdf->set_samples(num_samples);
}

inline void
GlossyReflector::set_ka(const double k) {
	this->ambient_brdf->set_kd(k);
}

inline void
GlossyReflector::set_ca(const double r, const double g, const double b) {
	this->ambient_brdf->set_cd(r, g, b);
}

inline void
GlossyReflector::set_kd(const double k) {
	this->diffuse_brdf->set_kd(k);
}

inline void
GlossyReflector::set_cd(const double r, const double g, const double b) {
	this->diffuse_brdf->set_cd(r, g, b);
}

inline void
GlossyReflector::set_ks(const double k) {
	this->specular_brdf->set_ks(k);
}

inline void
GlossyReflector::set_cs(const double r, const double g, const double b) {
	this->specular_brdf->set_cs(r, g, b);
}

inline void
GlossyReflector::set_exp_s(const double e) {
	this->specular_brdf->set_exponent(e);
}

inline void
GlossyReflector::set_kr(const double k) {
	this->reflected_brdf->set_ks(k);
}

inline void
GlossyReflector::set_cr(const double r, const double g, const double b) {
	this->reflected_brdf->set_cs(r, g, b);
}

inline void
GlossyReflector::set_exp_r(const double e) {
	this->reflected_brdf->set_exponent(e);
}
