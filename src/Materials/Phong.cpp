#include "Phong.h"
#include "../World/World.h"
#include <math.h>

Phong::Phong(void)
	: Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular)
{}

Phong::Phong(const Phong& rhs)
	: Material(rhs) 
{
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

Phong*
Phong::clone() const 
{
	return new Phong(*this);
}

Phong::~Phong() 
{
	if (this->ambient_brdf)
		delete this->ambient_brdf;

	if (this->diffuse_brdf)
		delete this->diffuse_brdf;

	if (this->specular_brdf)
		delete this->specular_brdf;
}

Phong&
Phong::operator=(const Phong& rhs) 
{
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
Phong::shade(ShadeRec& sr) const
{
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
Phong::area_light_shade(ShadeRec& sr) const
{
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
Phong::path_shade(ShadeRec& sr) const
{
	/*
	notes:
		-> outgoing direction w_o is the vector opposite to the cast ray (w_o = -sr.ray.d).
		-> the reflected ray has the hit point as the origin and its direction is computed by the brdf in the sample_f function.
		-> since there are multiple brdfs in this material, the outgoing direction will be selected randomly.
		-> the intensities in brdfs will serve as the weights for the random selection.
	*/

	// optimized code:
	
	Vector3D w_i_d, w_i_s;
	RGBColor f(this->diffuse_brdf->sample_f(sr, -sr.ray.d, w_i_d));
	f += this->specular_brdf->sample_f(sr, -sr.ray.d, w_i_s);

	double rand = rand_float(0, max(1.0, this->diffuse_brdf->get_kd() + specular_brdf->get_ks()));
	double running_threshold = this->diffuse_brdf->get_kd();

	if (rand < running_threshold) // diffuse reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_d), sr.depth + 1);
	
	running_threshold += this->specular_brdf->get_ks();

	if (rand < running_threshold) // specular reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_s), sr.w.vp.max_depth);

	return RGBColor(0, 0, 0); // light is absorbed (only happens when k_s + k_d < 1.0)
}

RGBColor
Phong::global_shade(ShadeRec& sr) const
{
	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}
