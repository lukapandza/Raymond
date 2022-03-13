#pragma once

#include "Material.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"

class Phong : public Material {

public:

	Phong(void); // default constructor

	Phong(const Phong& rhs); // copy constructor

	virtual Phong*
		clone(void) const;

	virtual //destructor
		~Phong(void);

	Phong& // assignment operator
		operator= (const Phong& rhs);

	// getters
	double
		get_kd() { return this->diffuse_brdf->get_kd(); }

	double
		get_ks() { return this->specular_brdf->get_ks(); }

	// setters

	void // set ambient intensity
		set_ka(const double  k);

	void // set diffuse color
		set_cd(const double  r, const double  g, const double  b);

	void // set diffuse intensity
		set_kd(const double k);

	void // set specular color
		set_cs(const double  r, const double  g, const double  b);

	void // set specular intensity
		set_ks(const double k);

	void // set both diffuse and specular colors
		set_c(const double  r, const double  g, const double  b);

	void // set specular exponent
		set_exp(const double e);

	void // set samples
		set_samples(const int num_samples);

	//functions

	virtual RGBColor
		shade(ShadeRec& sr);

	virtual RGBColor
		area_light_shade(ShadeRec& sr);

	virtual RGBColor
		path_shade(ShadeRec& sr);

	virtual RGBColor
		global_shade(ShadeRec& sr);

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

inline void // set ambient intensity
Phong::set_ka(const double  k) {
	this->ambient_brdf->set_kd(k);
}

inline void // set diffuse color
Phong::set_cd(const double  r, const double  g, const double  b) {
	this->ambient_brdf->set_cd(r, g, b);
	this->diffuse_brdf->set_cd(r, g, b);
}

inline void // set diffuse intensity
Phong::set_kd(const double k) {
	this->diffuse_brdf->set_kd(k);
}

inline void // set specular color
Phong::set_cs(const double  r, const double  g, const double  b) {
	this->specular_brdf->set_cs(r, g, b);
}

inline void // set specular intensity
Phong::set_ks(const double k) {
	this->specular_brdf->set_ks(k);
}

inline void // set both diffuse and specular colors
Phong::set_c(const double  r, const double  g, const double  b) {
	this->ambient_brdf->set_cd(r, g, b);
	this->diffuse_brdf->set_cd(r, g, b);
	this->specular_brdf->set_cs(r, g, b);
}

inline void // set specular exponent
Phong::set_exp(const double e) {
	this->specular_brdf->set_exponent(e);
}

inline void // set samples
Phong::set_samples(const int num_samples) {
	this->diffuse_brdf->set_samples(num_samples);
	this->specular_brdf->set_samples(num_samples);
}
