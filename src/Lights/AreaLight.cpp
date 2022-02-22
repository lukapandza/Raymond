#include "AreaLight.h"
#include "../World/World.h"

AreaLight::AreaLight(void) 
	: Light(),
	object_ptr(NULL),
	material_ptr(NULL)
{}

AreaLight::AreaLight(const AreaLight& rhs) 
	: Light(rhs) {

	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();
	else  object_ptr = NULL;

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();
	else  material_ptr = NULL;
}

AreaLight*
AreaLight::clone(void) const {
	return (new AreaLight(*this));
}

AreaLight::~AreaLight(void) {

	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}

AreaLight&
AreaLight::operator= (const AreaLight& rhs) {
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();

	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}

Vector3D
AreaLight::get_direction(ShadeRec& sr) {
	
	sample_point = object_ptr->sample();
	light_normal = object_ptr->get_normal(sample_point);
	w_i = sample_point - sr.hit_point;
	w_i.normalize();

	return w_i;
}

RGBColor
AreaLight::L(ShadeRec& sr) {

	double  n_dot_d = -light_normal * w_i;

	if (n_dot_d > 0.0)
		return material_ptr->get_Le(sr);
	else
		return black;
}

bool
AreaLight::in_shadow(const Ray& raymond, const ShadeRec& sr) const {
	
	double t;
	int num_objects = sr.w.objects.size();
	double ts = (sample_point - raymond.o) * raymond.d;

	for (int i = 0; i < num_objects; i++) {
		if (sr.w.objects[i]->shadow_hit(raymond, t) && t < ts)
			return true;
	}
	return false;
}

double 
AreaLight::G(const ShadeRec& sr) const {
	
	double  n_dot_d = -light_normal * w_i;
	double  d2 = sample_point.d_squared(sr.hit_point);

	return (n_dot_d / d2);
}

double 
AreaLight::pdf(ShadeRec& sr) const {
	return object_ptr->pdf(sr);
}
