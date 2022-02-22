#include "AmbientOccluder.h"
#include "../Samplers/MultiJittered.h"
#include "../World/World.h"

//default constructor:
AmbientOccluder::AmbientOccluder(void)
	: Light(),
	ls(1.0),
	color(1.0),
	u(Vector3D(0)),
	v(Vector3D(0)),
	w(Vector3D(0)),
	sampler_ptr(new MultiJittered(25)),
	min_amount(0)
{}

// copy constructor:
AmbientOccluder::AmbientOccluder(const AmbientOccluder& rhs) 
	: Light(rhs),
	ls(rhs.ls),
	color(rhs.color),
	u(rhs.u),
	v(rhs.v),
	w(rhs.w),
	min_amount(rhs.min_amount) {

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();
	else
		sampler_ptr = NULL;
}

// clone
AmbientOccluder*
AmbientOccluder::clone(void) const {
	return (new AmbientOccluder(*this));
}

// destructor:
AmbientOccluder::~AmbientOccluder(void) {

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

// assignemnt operator:
AmbientOccluder&
AmbientOccluder::operator= (const AmbientOccluder& rhs) {

	if (this == &rhs)
		return *this;

	Light::operator=(rhs);

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	ls = rhs.ls;
	color = rhs.color;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	min_amount = rhs.min_amount;

	return *this;
}

void
AmbientOccluder::set_sampler(Sampler* in_ptr) {
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	sampler_ptr = in_ptr;
	sampler_ptr->map_samples_to_hemisphere(1); //e = 1
}

Vector3D
AmbientOccluder::get_direction(ShadeRec& sr) {
	
	Point3D sp = sampler_ptr->sample_hemisphere();
	return (sp.x * u + sp.y * v + sp.z * w);
}

bool
AmbientOccluder::in_shadow(const Ray& raymond, const ShadeRec& sr) const {

	double t;
	int num_objects = sr.w.objects.size();

	for (int i = 0; i < num_objects; i++) {
		if (sr.w.objects[i]->shadow_hit(raymond, t))
			return true;
	}

	return false;
}

RGBColor
AmbientOccluder::L(ShadeRec& sr) {

	w = sr.normal;
	// in case normal is vertical:
	v = w ^ Vector3D(0.0034, 1.0, 0.0052);
	v.normalize();
	u = v ^ w;

	Ray shady_raymond;
	shady_raymond.o = sr.hit_point;
	shady_raymond.d = get_direction(sr);

	if (in_shadow(shady_raymond, sr))
		return (min_amount * ls * color);
	else
		return (ls * color);
}
