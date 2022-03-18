#pragma once

#include "BRDF.h"
#include "../Samplers/MultiJittered.h"

class GlossySpecular : public BRDF{

public:

	// default constructor
	GlossySpecular(); 

	// copy constructor
	GlossySpecular(const GlossySpecular& rhs); 

	// clone
	GlossySpecular* clone() const; 

	// destructor
	~GlossySpecular(); 

	//assignment operator
	GlossySpecular& operator= (const GlossySpecular& rhs);

	// get specular intensity
	double get_ks();

	// set specular intensity
	void set_ks(const double  c);

	// set highlight exponent
	void set_exponent(const double  c);

	// set specular color
	void set_cs(const double  c);

	// set diffuse color
	void set_cs(const double  r, const double  g, const double  b);
	
	// set diffuse color
	void set_cs(const RGBColor col);

	void set_samples(const int num_samples);

	void set_samples(const int num_samples, const double  exp);

	RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double & pdf) const;

private:

	// specular highlight intensity
	double  ks; 

	// specular highlight color
	RGBColor cs; 

	// specular exponent
	double  exp; 
};


inline void
GlossySpecular::set_ks(const double  c) 
{
	this->ks = c;
}

inline void
GlossySpecular::set_exponent(const double  c) 
{
	this->exp = c;
	this->sampler_ptr->map_samples_to_hemisphere(exp);
}

inline void
GlossySpecular::set_cs(const double  c) 
{
	this->cs = RGBColor(c, c, c);
}

inline void
GlossySpecular::set_cs(const double  r, const double  g, const double  b) 
{
	this->cs = RGBColor(r, g, b);
}

inline void
GlossySpecular::set_cs(const RGBColor col)
{
	this->cs = col;
}

inline void
GlossySpecular::set_samples(const int num_samples) 
{
	this->sampler_ptr = new MultiJittered(num_samples);
	this->sampler_ptr->map_samples_to_hemisphere(this->exp);
}

inline void
GlossySpecular::set_samples(const int num_samples, const double exp) 
{
	this->sampler_ptr = new MultiJittered(num_samples);
	this->sampler_ptr->map_samples_to_hemisphere(exp);
}

inline double
GlossySpecular::get_ks() 
{
	return this->ks;
}