#include "Phong2.h"
#include "../World/World.h"
#include <math.h>

// default constructor
Phong2::Phong2(void)
	: Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular)
{}

// copy constructor
Phong2::Phong2(const Phong2& rhs)
	: Material(rhs) {

	if (rhs.ambient_brdf)
		this->ambient_brdf = rhs.ambient_brdf->clone();
	else
		this->ambient_brdf = nullptr;

	if (rhs.diffuse_brdf)
		this->diffuse_brdf = rhs.diffuse_brdf->clone();
	else
		this->diffuse_brdf = nullptr;

	if (rhs.specular_brdf)
		this->specular_brdf = rhs.specular_brdf->clone();
	else
		this->specular_brdf = nullptr;
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

	if (this->diffuse_brdf)
		delete this->diffuse_brdf;

	if (this->specular_brdf)
		delete this->specular_brdf;

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

	if (this->diffuse_brdf) {
		delete this->diffuse_brdf;
		this->diffuse_brdf = nullptr;
	}

	if (rhs.diffuse_brdf)
		this->diffuse_brdf = rhs.diffuse_brdf->clone();

	if (this->specular_brdf) {
		delete this->specular_brdf;
		this->specular_brdf = nullptr;
	}

	if (rhs.specular_brdf)
		this->specular_brdf = rhs.specular_brdf->clone();

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
				L += (diffuse_brdf->f(sr, w_o, w_i) + specular_brdf->f(sr, w_o, w_i))
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
Phong2::path_shade(ShadeRec& sr) {

	/*
	notes:
		-> outgoing direction w_o is the vector opposite to the cast ray (w_o = -sr.ray.d).
		-> the reflected ray has the hit point as the origin and its direction is computed by the brdf in the sample_f function.
		-> since there are multiple brdfs in this material, the outgoing direction will be selected randomly.
		-> the intensities in brdfs will serve as the weights for the random selection.
		-> if the sampled material color is black, there is no need to cast further rays, as they are multiplied.
	*/

	/*
	Vector3D w_o = -sr.ray.d;
	Vector3D w_i_d, w_i_s;

	RGBColor f_d = this->diffuse_brdf->sample_f(sr, w_o, w_i_d);
	RGBColor f_s = this->specular_brdf->sample_f(sr, w_o, w_i_s);

	double k_d = this->diffuse_brdf->get_kd();
	double k_s = this->specular_brdf->get_ks();

	double rand = rand_float(0, 1.0);
	double p_d = k_d / (k_d + k_s);
	double p_s = 1.0 - p_d;
	
	Vector3D w_i = rand < p_d ? w_i_d : w_i_s;

	// using the p * f / k to allow for k_d + k_s >= 1.0 and still have energy conservation.
	return (p_d * f_d / k_d + p_s * f_s / k_s)
		* sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1);
	*/

	// optimized code:

	Vector3D w_i_d, w_i_s;
	RGBColor f = this->diffuse_brdf->sample_f(sr, -sr.ray.d, w_i_d);
	f += this->specular_brdf->sample_f(sr, -sr.ray.d, w_i_s);

	if (f.r == 0.0 && f.g == 0.0 && f.b == 0.0)
		return f;

	double rand = rand_float(0, 1.0);
	double running_threshold = this->diffuse_brdf->get_kd();

	if (rand < running_threshold) // diffuse reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_d), sr.depth + 1);
	
	running_threshold += this->specular_brdf->get_ks();

	if (rand < running_threshold) // specular reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_s), sr.depth + 1);

	return RGBColor(0, 0, 0); // light is absorbed (only happens when k_s + k_d < 1.0)
}

RGBColor
Phong2::global_shade(ShadeRec& sr) {

	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}
