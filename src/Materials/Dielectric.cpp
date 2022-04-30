#include "Dielectric.h"
#include "../World/World.h"

Dielectric::Dielectric()
	: Phong(),
	fresnel_brdf(new FresnelReflector),
	fresnel_btdf(new FresnelTransmitter)
{}

Dielectric::Dielectric(const Dielectric& rhs)
	: Phong(rhs),
	cf_in(rhs.cf_in),
	cf_out(rhs.cf_out),
	fresnel_brdf(rhs.fresnel_brdf),
	fresnel_btdf(rhs.fresnel_btdf)
{
	if (rhs.fresnel_brdf)
		fresnel_brdf = rhs.fresnel_brdf->clone();
	else
		fresnel_brdf = nullptr;

	if (rhs.fresnel_btdf)
		fresnel_btdf = rhs.fresnel_btdf->clone();
	else
		fresnel_btdf = nullptr;
}

Dielectric*
Dielectric::clone() const {
	return new Dielectric(*this);
}

Dielectric::~Dielectric()
{
	if (fresnel_brdf) {
		delete fresnel_brdf;
		fresnel_brdf = nullptr;
	}

	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = nullptr;
	}

	Phong::~Phong();
}

Dielectric&
Dielectric::operator=(const Dielectric& rhs)
{
	if (this == &rhs)
		return *this;

	Phong::operator=(rhs);

	if (fresnel_brdf) {
		delete fresnel_brdf;
		fresnel_brdf = nullptr;
	}

	if (rhs.fresnel_brdf)
		fresnel_brdf = rhs.fresnel_brdf->clone();

	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = nullptr;
	}

	if (rhs.fresnel_btdf)
		fresnel_btdf = rhs.fresnel_btdf->clone();

	return *this;
}

RGBColor 
Dielectric::shade(ShadeRec& sr) const 
{
	RGBColor L(Phong::shade(sr));
	Vector3D w_o(-sr.ray.d);

	Vector3D w_i;
	RGBColor fr = fresnel_brdf->sample_f(sr, w_o, w_i); // computes wi
	Ray reflected_ray(sr.hit_point, w_i);

	double t = kHugeValue;
	RGBColor Lr, Lt;

	double ndotwi = sr.normal * w_i;

	if (fresnel_btdf->tir(sr)) { // total internal reflection
		if (ndotwi < 0.0) {
			// reflected ray is inside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr; // inside filter color
		}
		else {
			// reflected ray is outside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			// kr = 1
			L += cf_out.powc(t) * Lr; // outside filter color
		}
	}
	else { // no total internal reflection
		Vector3D w_t;
		RGBColor ft = fresnel_btdf->sample_f(sr, w_o, w_t); // computes wt
		Ray transmitted_ray(sr.hit_point, w_t);

		double ndotwt = sr.normal * w_t;
		if (ndotwi < 0.0) {
			// reflected ray is inside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			Lr *= fr * fabs(ndotwi);
			L += cf_in.powc(t) * Lr; // inside filter color

			// transmitted ray is outside
			Lt = sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1);
			Lt *= ft * fabs(ndotwt);
			L += cf_out.powc(t) * Lt; // outside filter color
		}
		else {
			// reflected ray is outside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			Lr *= fr * fabs(ndotwi);
			L += cf_out.powc(t) * Lr; // outside filter color

			// transmitted ray is inside
			Lt = sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1);
			Lt *= ft * fabs(ndotwt);
			L += cf_in.powc(t) * Lt; // inside filter color
		}
	}

	return L;
}

RGBColor 
Dielectric::path_shade(ShadeRec& sr) const
{
	Vector3D w_i_d, w_i_s, w_i_r, w_i_t;
	RGBColor f(this->diffuse_brdf->sample_f(sr, -sr.ray.d, w_i_d));
	f += this->specular_brdf->sample_f(sr, -sr.ray.d, w_i_s);

	double k_r = fresnel_brdf->fresnel(sr);
	double k_t = fresnel_btdf->fresnel(sr);

	double rand = rand_float(0, 
		std::max(1.0, this->diffuse_brdf->get_kd() 
		+ specular_brdf->get_ks()
		+ k_r
		+ k_t));

	double running_threshold = this->diffuse_brdf->get_kd();

	if (rand < running_threshold) // diffuse reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_d), sr.depth + 1);

	running_threshold += this->specular_brdf->get_ks();

	if (rand < running_threshold) // specular reflection
		return f * sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_s), sr.w.vp.max_depth);
	/*
	running_threshold += k_r;

	if (rand < running_threshold) { // ray is reflected
		double t = kHugeValue;
		RGBColor f_r = this->fresnel_brdf->sample_f(sr, -sr.ray.d, w_i_r);
		RGBColor L_r = sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_r), t, sr.depth + 1);
		f += f_r * fabs(sr.normal * w_i_r) * cf_out.powc(t);
		f *= L_r;
		return f;
	}

	running_threshold += k_t;

	if (rand < running_threshold) { // ray is transmitted
		double t = kHugeValue;
		RGBColor f_t = this->fresnel_btdf->sample_f(sr, -sr.ray.d, w_i_t);
		RGBColor L_t = sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i_t), t, sr.depth + 1);
		f += f_t * fabs(sr.normal * w_i_t) * cf_in.powc(t);
		f *= L_t;
		return f;
	}
	*/

	RGBColor f_r = fresnel_brdf->sample_f(sr, -sr.ray.d, w_i_r); // computes wi
	Ray reflected_ray(sr.hit_point, w_i_r);

	double t = kHugeValue;
	RGBColor Lr, Lt;

	double n_dot_w_i_r = sr.normal * w_i_r;

	if (fresnel_btdf->tir(sr)) { // total internal reflection
		if (n_dot_w_i_r < 0.0) {
			// reflected ray is inside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			f += f_r * fabs(sr.normal * w_i_r) * cf_out.powc(t);
			f *= Lr; // inside filter color
		}
		else {
			// reflected ray is outside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			// kr = 1
			f *= cf_out.powc(t) * Lr; // outside filter color
		}
	}
	else { // no total internal reflection
		Vector3D w_t;
		RGBColor f_t = fresnel_btdf->sample_f(sr, -sr.ray.d, w_t); // computes wt
		Ray transmitted_ray(sr.hit_point, w_t);

		double n_dot_w_t = sr.normal * w_t;
		if (n_dot_w_i_r < 0.0) {
			// reflected ray is inside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			f += f_r * fabs(n_dot_w_i_r) * cf_in.powc(t) * Lr;
			f *= Lr; // inside filter color

			// transmitted ray is outside
			Lt = sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1);
			f += f_t * fabs(n_dot_w_t) * cf_out.powc(t);
			f *= Lt; // outside filter color
		}
		else {
			// reflected ray is outside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			f += f_r * fabs(n_dot_w_i_r) * cf_out.powc(t);
			f *= Lr; // outside filter color

			// transmitted ray is inside
			Lt = sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1);
			f += f_t * fabs(n_dot_w_t) * cf_in.powc(t);
			f *= Lt; // inside filter color
		}
	}

	return f; // light is absorbed(only happens when k_s + k_d + k_r + k_t < 1.0)
}

