#pragma once

#include "BRDF.h"
#include "../Samplers/MultiJittered.h"

class GlossySpecular : public BRDF{

public:

	GlossySpecular(void); // default constructor

	GlossySpecular(const GlossySpecular& rhs); // copy constructor

	virtual GlossySpecular*
		clone(void) const; // clone

	virtual
		~GlossySpecular(); // destructor

	GlossySpecular& //assignment operator
		operator= (const GlossySpecular& rhs);

	double
		get_ks();

	// setters

	void
		set_ks(const double  c);

	void
		set_exponent(const double  c);

	void // set diffuse color
		set_cs(const double  c);

	void // set diffuse color
		set_cs(const double  r, const double  g, const double  b);

	void // set diffuse color
		set_cs(const RGBColor col);

	void
		set_samples(const int num_samples);

	void
		set_samples(const int num_samples, const double  exp);

	// functions

	RGBColor
		f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	RGBColor
		sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double & pdf) const;

private:

	double  ks; // specular highlight intensity
	RGBColor cs; // specular highlight color
	double  exp; // specular exponent
};

// inlined functions:

inline void
GlossySpecular::set_ks(const double  c) {
	ks = c;
}

inline void
GlossySpecular::set_exponent(const double  c) {
	exp = c;
	sampler_ptr->map_samples_to_hemisphere(exp);
}

inline void
GlossySpecular::set_cs(const double  c) {
	cs = RGBColor(c, c, c);
}

inline void
GlossySpecular::set_cs(const double  r, const double  g, const double  b) {
	cs = RGBColor(r, g, b);
}

inline void
GlossySpecular::set_cs(const RGBColor col) {
	cs = col;
}

inline void
GlossySpecular::set_samples(const int num_samples) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(this->exp);
}

inline void
GlossySpecular::set_samples(const int num_samples, const double exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}

inline double
GlossySpecular::get_ks() {
	return this->ks;
}