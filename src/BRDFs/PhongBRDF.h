#pragma once

#include "BRDF.h"
#include "../Samplers/MultiJittered.h"

class PhongBRDF : public BRDF {

public:

	PhongBRDF(); // default constructor

	PhongBRDF(const PhongBRDF& rhs); // copy constructor

	PhongBRDF*
		clone() const; // clone

	~PhongBRDF(); // destructor

	PhongBRDF& // assignment operator
		operator= (const PhongBRDF& rhs);

	// getters:
	double
		get_kd() { return this->k_d; }

	double
		get_ks() { return this->k_s; }

	// setters:

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

	// functions

	RGBColor
		f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor
		sample_f(const ShadeRec& sr, Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double& pdf) const;

	RGBColor
		rho(const ShadeRec& sr, const Vector3D& w_o) const;

private:

	double k_d = 0.0; // diffuse intensity
	RGBColor c_d; // diffuse color

	double k_s = 0.0; // specular intensity
	double exp; // specular sharpness
	RGBColor c_s; // specular color

	Sampler* sampler_ptr_d; // diffuse sampler
	Sampler* sampler_ptr_s; // specular sampler
};

inline void
PhongBRDF::set_cd(const double  r, const double  g, const double  b) {
	this->c_d = RGBColor(r, g, b);
}

inline void
PhongBRDF::set_kd(const double k) {
	this->k_d = k;
}

inline void
PhongBRDF::set_cs(const double  r, const double  g, const double  b) {
	this->c_s = RGBColor(r, g, b);
}

inline void
PhongBRDF::set_ks(const double k) {
	this->k_s = k;
}

inline void
PhongBRDF::set_c(const double  r, const double  g, const double  b) {
	this->set_cd(r, g, b);
	this->set_cs(r, g, b);
}

inline void
PhongBRDF::set_exp(const double e) {
	this->exp = e;
	this->sampler_ptr_s->map_samples_to_hemisphere(this->exp);
}

inline void
PhongBRDF::set_samples(const int num_samples) {

	this->sampler_ptr_d = new MultiJittered(num_samples);
	this->sampler_ptr_d->map_samples_to_hemisphere(0);

	this->sampler_ptr_s = new MultiJittered(num_samples);
	this->sampler_ptr_s->map_samples_to_hemisphere(this->exp);
}