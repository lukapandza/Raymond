#pragma once

#include "Phong.h"

class GlossyReflector : public Phong {

public:

	GlossyReflector(void);

	GlossyReflector(const GlossyReflector& rhs);

	GlossyReflector*
		clone(void) const;

	~GlossyReflector(void);

	GlossyReflector&
		operator=(const GlossyReflector& rhs);

	void
		set_samples(const int num_samples, const double  exp);

	void
		set_kr(const double  k);

	void
		set_cr(const double  c);

	void 
		set_cr(const double  r, const double  g, const double  b);

	void
		set_cr(const RGBColor& col);

	void
		set_exponent(const double  exp);

	virtual RGBColor
		area_light_shade(ShadeRec& sr);

private:

	GlossySpecular* glossy_specular_brdf;
};

inline void
GlossyReflector::set_samples(const int num_samples, const double  exp) {
	glossy_specular_brdf->set_samples(num_samples, exp);
}

inline void
GlossyReflector::set_kr(const double  k) {
	glossy_specular_brdf->set_ks(k);
}

inline void
GlossyReflector::set_cr(const double  c) {
	glossy_specular_brdf->set_cs(c);
}

inline void
GlossyReflector::set_cr(const double  r, const double  g, const double  b) {
	glossy_specular_brdf->set_cs(r, g, b);
}

inline void
GlossyReflector::set_cr(const RGBColor& col) {
	glossy_specular_brdf->set_cs(col);
}

inline void
GlossyReflector::set_exponent(const double  exp) {
	glossy_specular_brdf->set_exponent(exp);
}