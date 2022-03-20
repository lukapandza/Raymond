#include "GlossyReflector.h"
#include "World/World.h"

GlossyReflector::GlossyReflector()
	: ambient_brdf(new Lambertian),
	diffuse_brdf(new Lambertian),
	specular_brdf(new GlossySpecular),
	reflected_brdf(new GlossySpecular)
{}

GlossyReflector::GlossyReflector(const GlossyReflector& rhs) 
{
	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
	else
		ambient_brdf = nullptr;

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();
	else
		diffuse_brdf = nullptr;

	if (rhs.specular_brdf)
		specular_brdf = rhs.specular_brdf->clone();
	else
		specular_brdf = nullptr;

	if (rhs.reflected_brdf)
		reflected_brdf = rhs.reflected_brdf->clone();
	else
		reflected_brdf = nullptr;
}

GlossyReflector*
GlossyReflector::clone() const 
{
	return new GlossyReflector(*this);
}

GlossyReflector::~GlossyReflector()
{
	if (ambient_brdf)
		delete ambient_brdf;

	if (diffuse_brdf)
		delete diffuse_brdf;

	if (specular_brdf)
		delete specular_brdf;

	if (reflected_brdf)
		delete reflected_brdf;
}

GlossyReflector&
GlossyReflector::operator=(const GlossyReflector& rhs)
{
	if (this == &rhs)
		return *this;

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

	if (this->reflected_brdf) {
		delete this->reflected_brdf;
		this->reflected_brdf = nullptr;
	}

	if (rhs.reflected_brdf)
		this->reflected_brdf = rhs.reflected_brdf->clone();

	return *this;
}

RGBColor
GlossyReflector::area_light_shade(ShadeRec& sr) const
{
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

	Vector3D w_i;
	double pdf;
	RGBColor f_r = this->reflected_brdf->sample_f(sr, w_o, w_i, pdf);
	Ray reflected_ray(sr.hit_point, w_i);

	L += f_r * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i) / pdf;

	return L;
}

RGBColor
GlossyReflector::path_shade(ShadeRec& sr) const
{
	/*
	notes:
		-> outgoing direction w_o is the vector opposite to the cast ray (w_o = -sr.ray.d).
		-> the reflected ray has the hit point as the origin and its direction is computed by the brdf in the sample_f function.
		-> since there are multiple brdfs in this material, the outgoing direction will be selected randomly.
		-> the intensities in brdfs will serve as the weights for the random selection.
		-> if the sampled material color is black, there is no need to cast further rays, as they are multiplied.
	*/

	// optimized code:

	Vector3D w_i_d, w_i_s, w_i_r;

	RGBColor f = this->diffuse_brdf->sample_f(sr, -sr.ray.d, w_i_d);
	f += this->specular_brdf->sample_f(sr, -sr.ray.d, w_i_s);
	f += this->reflected_brdf->sample_f(sr, -sr.ray.d, w_i_r);

	if (f.r == 0.0 && f.g == 0.0 && f.b == 0.0)
		return f;
	
	double rand = rand_float(0, 1.0);
	double running_threshold = this->diffuse_brdf->get_kd();

	if (rand < running_threshold) // diffuse reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_d), sr.depth + 1);

	running_threshold += this->specular_brdf->get_ks();

	if (rand < running_threshold) // specular reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_s), sr.depth + 1);

	running_threshold += this->reflected_brdf->get_ks();

	if (rand < running_threshold) // reflected reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_r), sr.depth + 1);

	return RGBColor(0, 0, 0); // light is absorbed (only happens when k_s + k_d + k_r < 1.0)
}

RGBColor
GlossyReflector::global_shade(ShadeRec& sr) const
{
	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}
