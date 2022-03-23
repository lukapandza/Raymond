#include "Reflective.h"
#include "../World/World.h"

Reflective::Reflective()
	: Phong(),
	reflective_brdf(new PerfectSpecular)
{}

Reflective::Reflective(const Reflective& rhs) 
	: Phong(rhs) 
{
	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();
	else
		reflective_brdf = nullptr;
}

Reflective*
Reflective::clone() const {
	return new Reflective(*this);
}

Reflective::~Reflective() 
{
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = nullptr;
	}

	Phong::~Phong();
}

Reflective&
Reflective::operator=(const Reflective& rhs) 
{
	if (this == &rhs)
		return *this;

	Phong::operator=(rhs);

	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = nullptr;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return *this;
}

RGBColor
Reflective::shade(ShadeRec& sr) const
{
	RGBColor L(Phong::shade(sr)); // direct illumination
	Vector3D w_o = -sr.ray.d;
	Vector3D w_i;

	RGBColor fr = reflective_brdf->sample_f(sr, w_i, w_o);
	Ray reflected_ray(sr.hit_point, w_i);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i);

	return L;
}

RGBColor
Reflective::area_light_shade(ShadeRec& sr) const 
{
	RGBColor L(Phong::area_light_shade(sr));
	Vector3D w_o = -sr.ray.d;
	Vector3D w_i;

	RGBColor fr = reflective_brdf->sample_f(sr, w_i, w_o);
	Ray reflected_ray(sr.hit_point, w_i);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * w_i);

	return L;
}

RGBColor
Reflective::path_shade(ShadeRec& sr) const 
{
	/*
	notes:
		-> outgoing direction w_o is the vector opposite to the cast ray (w_o = -sr.ray.d).
		-> the reflected ray has the hit point as the origin and its direction is computed by the brdf in the sample_f function.
		-> since there are multiple brdfs in this material, the outgoing direction will be selected randomly.
		-> the intensities in brdfs will serve as the weights for the random selection.
		-> the specular highlight reflection only needs to compute for direct or directly reflected light sources.
	*/

	// optimized code:
	
	Vector3D w_i_d, w_i_s, w_i_r;
	RGBColor f(this->diffuse_brdf->sample_f(sr, -sr.ray.d, w_i_d));
	f += this->specular_brdf->sample_f(sr, -sr.ray.d, w_i_s);
	f += this->reflective_brdf->sample_f(sr, -sr.ray.d, w_i_r);

	double rand = rand_float(0, max(1.0, this->diffuse_brdf->get_kd() + specular_brdf->get_ks() + reflective_brdf->get_kr()));
	double running_threshold = this->diffuse_brdf->get_kd();

	if (rand < running_threshold) // diffuse reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_d), sr.depth + 1);

	running_threshold += this->specular_brdf->get_ks();

	if (rand < running_threshold) // specular reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_s), sr.w.vp.max_depth);

	running_threshold += this->reflective_brdf->get_kr();

	if (rand < running_threshold) // reflective reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_r), sr.depth + 1);


	return RGBColor(0, 0, 0); // light is absorbed (only happens when k_s + k_d < 1.0)
	
	/*
	RGBColor L(Phong::path_shade(sr));
	Vector3D w_i;
	RGBColor fr = reflective_brdf->sample_f(sr, -sr.ray.d, w_i);

	return L + fr * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1);
	*/
}

RGBColor
Reflective::global_shade(ShadeRec& sr) const 
{
	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}