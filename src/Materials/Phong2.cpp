#include "Phong2.h"
#include "../World/World.h"
#include <math.h>

// default constructor
Phong2::Phong2(void)
	: Material(),
	ambient_brdf(new Lambertian),
	brdf(new PhongBRDF)
{}

// copy constructor
Phong2::Phong2(const Phong2& rhs)
	: Material(rhs) {

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
	else
		ambient_brdf = nullptr;

	if (rhs.brdf)
		brdf = rhs.brdf->clone();
	else
		brdf = nullptr;
}

// clone
Phong2*
Phong2::clone(void) const {
	return new Phong2(*this);
}

// destructor
Phong2::~Phong2(void) {

	if (this->ambient_brdf)
		delete this->ambient_brdf;

	if (this->brdf)
		delete this->brdf;

	Material::~Material();
}

// assignmnet operator
Phong2&
Phong2::operator=(const Phong2& rhs) {

	if (this == &rhs)
		return *this;

	Material::operator=(rhs);

	if (this->ambient_brdf) {
		delete this->ambient_brdf;
		this->ambient_brdf = nullptr;
	}

	if (rhs.ambient_brdf)
		this->ambient_brdf = rhs.ambient_brdf->clone();

	if (this->brdf) {
		delete this->brdf;
		this->brdf = nullptr;
	}

	if (rhs.brdf)
		this->brdf = rhs.brdf->clone();

	return *this;
}

RGBColor
Phong2::shade(ShadeRec& sr) {

	Vector3D w_o(-sr.ray.d);
	RGBColor L = this->ambient_brdf->rho(sr, w_o) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();

	for (int i = 0; i < num_lights; i++) {

		Vector3D w_i = sr.w.lights[i]->get_direction(sr);
		double  n_dot_w_i = sr.normal * w_i;

		if (n_dot_w_i > 0.0) {

			bool in_shadow = false;

			if (sr.w.lights[i]->casts_shadows()) {

				Ray shadow_ray(sr.hit_point, w_i);
				in_shadow = sr.w.lights[i]->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += this->brdf->f(sr, w_o, w_i)
				* sr.w.lights[i]->L(sr)
				* n_dot_w_i;
		}
	}

	return L;
}

RGBColor
Phong2::area_light_shade(ShadeRec& sr) {

	Vector3D w_o(-sr.ray.d);
	RGBColor L = this->ambient_brdf->rho(sr, w_o) * sr.w.ambient_ptr->L(sr);

	int num_lights = sr.w.lights.size();

	for (int i = 0; i < num_lights; i++) {

		Vector3D w_i = sr.w.lights[i]->get_direction(sr);
		double  n_dot_w_i = sr.normal * w_i;

		if (n_dot_w_i > 0.0) {

			bool in_shadow = false;

			if (sr.w.lights[i]->casts_shadows()) {

				Ray shadow_ray(sr.hit_point, w_i);
				in_shadow = sr.w.lights[i]->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow) {

				L += this->brdf->f(sr, w_o, w_i)
					* sr.w.lights[i]->L(sr) * n_dot_w_i
					* sr.w.lights[i]->G(sr) * n_dot_w_i
					/ sr.w.lights[i]->pdf(sr);
			}
		}
	}

	return L;
}

RGBColor
Phong2::path_shade(ShadeRec& sr) {

	Vector3D w_o = -sr.ray.d;

	Vector3D w_i;
	double pdf;
	RGBColor f = this->brdf->sample_f(sr, w_o, w_i, pdf);
	RGBColor reflected_d = sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1);

	return f * reflected_d;
	
}

RGBColor
Phong2::global_shade(ShadeRec& sr) {

	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}
