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


	/* This code is much clearer but it was slowing down the renders significantly. Will leave it here as a reference:
	Vector3D w_i_d;
	Vector3D w_i_s;

	Vector3D w_o = -sr.ray.d;

	double pdf_d;
	double pdf_s;

	RGBColor f_d = diffuse_brdf->sample_f(sr, w_o, w_i_d, pdf_d);
	RGBColor f_s = specular_brdf->sample_f(sr, w_o, w_i_s, pdf_s);

	double  n_dot_wi_d = sr.normal * w_i_d;
	double  n_dot_wi_s = sr.normal * w_i_s;

	Ray reflected_ray_d(sr.hit_point, w_i_d);
	Ray reflected_ray_s(sr.hit_point, w_i_s);

	RGBColor reflected_color_d = sr.w.tracer_ptr->trace_ray(reflected_ray_d, sr.depth + 1);
	RGBColor reflected_color_s = sr.w.tracer_ptr->trace_ray(reflected_ray_s, sr.depth + 1);

	RGBColor col_d = f_d * reflected_color_d * n_dot_wi_d / pdf_d;
	RGBColor col_s = f_s * reflected_color_s * n_dot_wi_s / pdf_s;

	return col_d + col_s;
	*/
	
	RGBColor L(0);

	Vector3D w_o = -sr.ray.d;

	Vector3D w_i;
	double pdf;

	L += diffuse_brdf->sample_f(sr, w_o, w_i, pdf) // diffuse contribution
		* (sr.normal * w_i) // n dot w_i
		* sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1) // tracing the reflected ray
		/ pdf;

	// note: w_i and pdf get overwritten in next line: reusing them to save memory and initialization cost

	L += specular_brdf->sample_f(sr, w_o, w_i, pdf) // specular contribution
		* (sr.normal * w_i) // n dot w_i
		* sr.w.tracer_ptr->trace_ray(Ray(sr.hit_point, w_i), sr.depth + 1) // tracing the reflected ray
		/ pdf;

	return L;

}

RGBColor
Phong::global_shade(ShadeRec& sr) {

	RGBColor L(0);
	if (sr.depth == 0)
		L = this->area_light_shade(sr);

	RGBColor f = this->path_shade(sr);

	return L + f;
}