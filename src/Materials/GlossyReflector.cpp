#include "GlossyReflector.h"
#include "../World/World.h"

GlossyReflector::GlossyReflector(void)
	: Phong(),
	glossy_specular_brdf(new GlossySpecular)
{}

GlossyReflector::GlossyReflector(const GlossyReflector& rhs)
	: Phong(rhs) {
	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = rhs.glossy_specular_brdf->clone();
	else
		glossy_specular_brdf = NULL;
}

GlossyReflector*
GlossyReflector::clone(void) const {
	return new GlossyReflector(*this);
}

GlossyReflector::~GlossyReflector(void) {

	Phong::~Phong();

	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}
}

GlossyReflector&
GlossyReflector::operator=(const GlossyReflector& rhs) {

	if (this == &rhs)
		return *this;

	Phong::operator=(rhs);

	if (glossy_specular_brdf) {
		delete glossy_specular_brdf;
		glossy_specular_brdf = NULL;
	}

	if (rhs.glossy_specular_brdf)
		glossy_specular_brdf = rhs.glossy_specular_brdf->clone();

	return *this;
}

RGBColor
GlossyReflector::area_light_shade(ShadeRec& sr) {
	
	RGBColor L(Phong::area_light_shade(sr)); // direct illumination
	
	Vector3D w_o(-sr.ray.d);
	Vector3D w_i;
	double  pdf;

	RGBColor fr(glossy_specular_brdf->sample_f(sr, w_o, w_i, pdf));
	Ray reflected_ray(sr.hit_point, w_i);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i) / pdf;

	return L;
}
