#include "Matte.h"
#include "../World/World.h"

Matte::Matte()
	: Material(),
	ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian)
{}

Matte::Matte(const Matte& rhs)
	: Material(rhs) 
{
	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
	else
		ambient_brdf = nullptr;

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();
	else
		diffuse_brdf = nullptr;
}

Matte*
Matte::clone() const 
{
	return new Matte(*this);
}

Matte::~Matte() 
{
	if (ambient_brdf)
		delete ambient_brdf;

	if (diffuse_brdf)
		delete diffuse_brdf;
}

Matte&
Matte::operator=(const Matte& rhs) 
{
	if (this == &rhs)
		return *this;

	Material::operator=(rhs);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = nullptr;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = nullptr;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return *this;
}

RGBColor
Matte::shade(ShadeRec& sr) const 
{
	Vector3D w_o = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, w_o) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();

	for (int i = 0; i < num_lights; i++) {

		Vector3D w_i = sr.w.lights[i]->get_direction(sr);
		double  normal_dot_w_i = sr.normal * w_i;

		if (normal_dot_w_i > 0.0) {

			bool in_shadow = false;

			if (sr.w.lights[i]->casts_shadows()) {

				Ray shadow_ray(sr.hit_point, w_i);
				in_shadow = sr.w.lights[i]->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, w_o, w_i)
				* sr.w.lights[i]->L(sr)
				* normal_dot_w_i;
		}
	}

	return L;
}

RGBColor
Matte::area_light_shade(ShadeRec& sr) const
{
	Vector3D w_o = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, w_o) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();

	for (int i = 0; i < num_lights; i++) {

		Vector3D w_i = sr.w.lights[i]->get_direction(sr);
		double  normal_dot_w_i = sr.normal * w_i;

		if (normal_dot_w_i > 0.0) {

			bool in_shadow = false;

			if (sr.w.lights[i]->casts_shadows()) {

				Ray shadow_ray(sr.hit_point, w_i);
				in_shadow = sr.w.lights[i]->in_shadow(shadow_ray, sr);
			}

			if (!in_shadow)
				L += diffuse_brdf->f(sr, w_o, w_i)
				* sr.w.lights[i]->L(sr)
				* sr.w.lights[i]->G(sr)
				* normal_dot_w_i
				/ sr.w.lights[i]->pdf(sr);
		}
	}

	return L;
}

RGBColor
Matte::path_shade(ShadeRec& sr) const
{
	/*
	notes:
		-> outgoing direction w_o is the vector opposite to the cast ray (w_o = -sr.ray.d).
		-> the reflected ray has the hit point as the origin and its direction is computed by the brdf in the sample_f function.
	*/

	// optimized code:

	Vector3D w_i;
	RGBColor f(diffuse_brdf->sample_f(sr, -sr.ray.d, w_i));

	return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1);
}

RGBColor
Matte::global_shade(ShadeRec& sr) const 
{
	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}