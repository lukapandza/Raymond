#pragma once

#include "Phong.h"
#include "../BRDFs/PerfectSpecular.h"

class Reflective : public Phong {

public:

	Reflective(void);

	Reflective(const Reflective& rhs);

	Reflective*
		clone(void) const;

	~Reflective(void);

	Reflective&
		operator = (const Reflective& rhs);

	void 
		set_kr(const double  c);

	void 
		set_cr(const double  c);

	void
		set_cr(const double  r, const double  g, const double  b);

	void
		set_cr(const RGBColor& col);

	RGBColor
		shade(ShadeRec& sr);

	RGBColor
		area_light_shade(ShadeRec& sr);

	RGBColor
		path_shade(ShadeRec& sr);

private:

	PerfectSpecular* reflective_brdf;
};

inline void
Reflective::set_kr(const double  c) {
	reflective_brdf->set_kr(c);
}

inline void
Reflective::set_cr(const double  c) {
	reflective_brdf->set_cr(c);
}

inline void
Reflective::set_cr(const double  r, const double  g, const double  b) {
	reflective_brdf->set_cr(r, g, b);
}

inline void
Reflective::set_cr(const RGBColor& col) {
	reflective_brdf->set_cr(col);
}