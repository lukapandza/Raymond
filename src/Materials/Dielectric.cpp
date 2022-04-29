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
			//Lr = Lr == RGBColor(0, 0, 0) ? RGBColor(1, 1, 1) : Lr;
			L += cf_in.powc(t) * Lr; // inside filter color
		}
		else {
			// reflected ray is outside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			//Lr = Lr == RGBColor(0, 0, 0) ? RGBColor(1, 1, 1) : Lr;
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
			//Lr = Lr == RGBColor(0, 0, 0) ? RGBColor(1, 1, 1) : Lr;
			Lr *= fr * fabs(ndotwi);
			L += cf_in.powc(t) * Lr; // inside filter color

			// transmitted ray is outside
			Lt = sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1);
			//Lt = Lt == RGBColor(0, 0, 0) ? RGBColor(1, 1, 1) : Lt;
			Lt *= ft * fabs(ndotwt);
			L += cf_out.powc(t) * Lt; // outside filter color
		}
		else {
			// reflected ray is outside
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			//Lr = Lr == RGBColor(0, 0, 0) ? RGBColor(1, 1, 1) : Lr;
			Lr *= fr * fabs(ndotwi);
			L += cf_out.powc(t) * Lr; // outside filter color

			// transmitted ray is inside
			Lt = sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1);
			//Lt = Lt == RGBColor(0, 0, 0) ? RGBColor(1, 1, 1) : Lt;
			Lt *= ft * fabs(ndotwt);
			L += cf_in.powc(t) * Lt; // inside filter color
		}
	}

	return L;
}
