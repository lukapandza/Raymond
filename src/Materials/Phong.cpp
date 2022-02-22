#include "Phong.h"
#include "../World/World.h"

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
				L += (diffuse_brdf->f(sr, w_o, w_i) + specular_brdf->f(sr, w_o, w_i)) * sr.w.lights[i]->L(sr) * n_dot_w_i;
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

			if (!in_shadow)
				L += (diffuse_brdf->f(sr, w_o, w_i) + specular_brdf->f(sr, w_o, w_i)) * sr.w.lights[i]->L(sr) * n_dot_w_i * sr.w.lights[i]->G(sr) * n_dot_w_i / sr.w.lights[i]->pdf(sr);
		}

	}

	return L;
}