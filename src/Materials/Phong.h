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

	//setters
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
		set_ks(const double  c);

	void
		set_exp(const double  c);

	void
		set_cs(const double  c);

	void
		set_cs(const double  r, const double  g, const double  b);

	void
		set_cs(const RGBColor& col);

	void
		set_samples(const int num_samples, const double exp);

	//functions

	virtual RGBColor
		shade(ShadeRec& sr);

	virtual RGBColor
		area_light_shade(ShadeRec& sr);

	virtual RGBColor
		path_shade(ShadeRec& sr);

protected:

	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
	GlossySpecular* specular_brdf;
};

// inlined functions

inline void
Phong::set_ka(const double  c) {
	ambient_brdf->set_kd(c);
}

inline void
Phong::set_kd(const double  c) {
	diffuse_brdf->set_kd(c);
}

inline void
Phong::set_cd(const double  c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}

inline void
Phong::set_cd(const double  r, const double  g, const double  b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

inline void
Phong::set_cd(const RGBColor& col) {
	ambient_brdf->set_cd(col);
	diffuse_brdf->set_cd(col);
}

inline void
Phong::set_ks(const double  c) {
	specular_brdf->set_ks(c);
}

inline void
Phong::set_exp(const double  c) {
	specular_brdf->set_exponent(c);
}

inline void
Phong::set_cs(const double  c) {
	specular_brdf->set_cs(c);
}

inline void
Phong::set_cs(const double  r, const double  g, const double  b) {
	specular_brdf->set_cs(r, g, b);
}

inline void
Phong::set_cs(const RGBColor& col) {
	specular_brdf->set_cs(col);
}

inline void
Phong::set_samples(const int num_samples, const double exp) {
	diffuse_brdf->set_samples(num_samples);
	specular_brdf->set_samples(num_samples, exp);
}