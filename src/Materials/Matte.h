#pragma once

#include "Material.h"
#include "../BRDFs/Lambertian.h"

class Matte : public Material {

public:

	Matte(); // default constructor

	Matte(const Matte& rhs); // copy constructor

	virtual Matte*
		clone() const;

	virtual // destructor
		~Matte();

	Matte& // assignment operator
		operator= (const Matte& rhs);

	// setters

	void
		set_ka(const double  k);

	void
		set_kd(const double  k);

	void
		set_cd(const double  c);

	void
		set_cd(const double  r, const double  g, const double  b);

	void
		set_cd(const RGBColor& col);

	void
		set_samples(const int& n);

	// functions

	RGBColor
		shade(ShadeRec& sr);

	RGBColor
		area_light_shade(ShadeRec& sr);

	RGBColor
		path_shade(ShadeRec& sr);

	RGBColor
		global_shade(ShadeRec& sr);

private:

	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
};

// inlined functions

inline void
Matte::set_ka(const double  c) {
	ambient_brdf->set_kd(c);
}

inline void
Matte::set_kd(const double  c) {
	diffuse_brdf->set_kd(c);
}

inline void
Matte::set_cd(const double  c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Matte::set_cd(const double  r, const double  g, const double  b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void
Matte::set_cd(const RGBColor& col) {
	ambient_brdf->set_cd(col);
	diffuse_brdf->set_cd(col);
}

inline void
Matte::set_samples(const int& n) {
	diffuse_brdf->set_samples(n);
}