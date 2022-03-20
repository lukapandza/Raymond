#pragma once

#include "Material.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"

class Phong : public Material {

public:

	// default constructor
	Phong();

	// copy constructor
	Phong(const Phong& rhs); 

	// clone
	virtual Phong* clone() const;

	//destructor
	virtual ~Phong();

	// assignment operator
	Phong& operator= (const Phong& rhs);

	// set ambient intensity
	void set_ka(const double  k);

	// set diffuse color
	void set_cd(const double  r, const double  g, const double  b);

	// set diffuse intensity
	void set_kd(const double k);

	// set specular color
	void set_cs(const double  r, const double  g, const double  b);

	// set specular intensity
	void set_ks(const double k);

	// set both diffuse and specular colors
	void set_c(const double  r, const double  g, const double  b);

	// set specular exponent
	void set_exp(const double e);

	// set samples
	void set_samples(const int num_samples);

	virtual RGBColor shade(ShadeRec& sr) const;

	virtual RGBColor area_light_shade(ShadeRec& sr) const;

	virtual RGBColor path_shade(ShadeRec& sr) const;

	virtual RGBColor global_shade(ShadeRec& sr) const;

protected:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

inline void
Phong::set_ka(const double  k) 
{
	this->ambient_brdf->set_kd(k);
}

inline void
Phong::set_cd(const double  r, const double  g, const double  b) 
{
	this->ambient_brdf->set_cd(r, g, b);
	this->diffuse_brdf->set_cd(r, g, b);
}

inline void
Phong::set_kd(const double k) 
{
	this->diffuse_brdf->set_kd(k);
}

inline void
Phong::set_cs(const double  r, const double  g, const double  b) 
{
	this->specular_brdf->set_cs(r, g, b);
}

inline void
Phong::set_ks(const double k) 
{
	this->specular_brdf->set_ks(k);
}

inline void
Phong::set_c(const double  r, const double  g, const double  b) 
{
	this->ambient_brdf->set_cd(r, g, b);
	this->diffuse_brdf->set_cd(r, g, b);
	this->specular_brdf->set_cs(r, g, b);
}

inline void
Phong::set_exp(const double e) 
{
	this->specular_brdf->set_exponent(e);
}

inline void
Phong::set_samples(const int num_samples) 
{
	this->diffuse_brdf->set_samples(num_samples);
	this->specular_brdf->set_samples(num_samples);
}
