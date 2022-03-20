#pragma once

#include "Material.h"
#include "../BRDFs/Lambertian.h"

class Matte : public Material {

public:

	// default constructor
	Matte(); 

	// copy constructor
	Matte(const Matte& rhs); 

	virtual Matte* clone() const;

	// destructor
	virtual ~Matte();

	// assignment operator
	Matte& operator= (const Matte& rhs);

	// set ambient intensity
	void set_ka(const double k);

	// set diffuse intensity
	void set_kd(const double k);

	// set diffuse greyscale color
	void set_cd(const double c);

	// set diffuse color by component
	void set_cd(const double r, const double g, const double b);

	// set diffuse color by reference
	void set_cd(const RGBColor& col);

	// set number of samples for Lambertian brdf
	void set_samples(const int& n);

	// functions

	RGBColor shade(ShadeRec& sr) const;

	RGBColor area_light_shade(ShadeRec& sr) const;

	RGBColor path_shade(ShadeRec& sr) const;

	RGBColor global_shade(ShadeRec& sr) const;

private:

	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};


inline void
Matte::set_ka(const double c) 
{
	ambient_brdf->set_kd(c);
}

inline void
Matte::set_kd(const double c) 
{
	diffuse_brdf->set_kd(c);
}

inline void
Matte::set_cd(const double c) 
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Matte::set_cd(const double  r, const double  g, const double  b) 
{
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void
Matte::set_cd(const RGBColor& col) 
{
	ambient_brdf->set_cd(col);
	diffuse_brdf->set_cd(col);
}

inline void
Matte::set_samples(const int& n) 
{
	diffuse_brdf->set_samples(n);
}