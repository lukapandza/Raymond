#include "Phong.h"
#include "../World/World.h"
#include <math.h>

// default constructor
Phong::Phong(void) 
	: Material(),
	ambient_brdf(new Lambertian()),
	diffuse_brdf(new Lambertian()),
	specular_brdf(new GlossySpecular())
{}

// copy constructor
Phong::Phong(const Phong& rhs)
	: Material(rhs) {

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
	else
		ambient_brdf = NULL;

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();
	else
		diffuse_brdf = NULL;

	if (rhs.specular_brdf)
		specular_brdf = rhs.specular_brdf->clone();
	else
		specular_brdf = NULL;
}

// clone
Phong*
Phong::clone(void) const {
	return new Phong(*this);
}

// destructor
Phong::~Phong(void) {
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}
}

// assignmnet operator
Phong&
Phong::operator=(const Phong& rhs) {
	
	if (this == &rhs)
		return *this;

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	if (specular_brdf) {
		delete specular_brdf;
		specular_brdf = NULL;
	}

	if (rhs.specular_brdf)
		specular_brdf = rhs.specular_brdf->clone();

	return *this;
}

RGBColor
Phong::shade(ShadeRec& sr) {
	
	Vector3D w_o(-sr.ray.d);
	RGBColor L = ambient_brdf->rho(sr, w_o) * sr.w.ambient_ptr->L(sr);
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
				L += (diffuse_brdf->f(sr, w_o, w_i) + specular_brdf->f(sr, w_o, w_i)) 
					* sr.w.lights[i]->L(sr) 
					* n_dot_w_i;
		}
	}

	return L;
}

RGBColor
Phong::area_light_shade(ShadeRec& sr) {

	Vector3D w_o(-sr.ray.d);
	RGBColor L = ambient_brdf->rho(sr, w_o) * sr.w.ambient_ptr->L(sr);

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

				L += (diffuse_brdf->f(sr, w_o, w_i) + specular_brdf->f(sr, w_o, w_i))
					* sr.w.lights[i]->L(sr) * n_dot_w_i
					* sr.w.lights[i]->G(sr) * n_dot_w_i
					/ sr.w.lights[i]->pdf(sr);
			}
		}
	}

	return L;
}

RGBColor
Phong::path_shade(ShadeRec& sr) {

	Vector3D w_o = -sr.ray.d;

	Vector3D w_i_d;
	double pdf_d;
	RGBColor f_d = this->diffuse_brdf->sample_f(sr, w_o, w_i_d, pdf_d);
	RGBColor reflected_d = sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_d), sr.depth + 1);

	Vector3D w_i_s;
	double pdf_s;
	RGBColor f_s = this->specular_brdf->sample_f(sr, w_o, w_i_s, pdf_s);
	RGBColor reflected_s = sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_s), sr.depth + 1);

	return f_d * reflected_d * (sr.normal * w_i_d) / pdf_d
		+ f_s * reflected_s * (sr.normal * w_i_s) / pdf_s;
}

RGBColor
Phong::global_shade(ShadeRec& sr) {

	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}