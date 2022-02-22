#include "PointLight.h"
#include "../World/World.h"

// default constructor:
PointLight::PointLight(void)
	: Light(),
	ls(1.0),
	color(1.0),
	location(Point3D(0.0, 0.0, 0.0)),
	da(1.0)
{}

// copy constructor:
PointLight::PointLight(const PointLight& rhs)
	: Light(rhs),
	ls(rhs.ls),
	color(rhs.color),
	location(rhs.location),
	da(rhs.da)
{}

// clone
PointLight*
PointLight::clone(void) const {
	return (new PointLight(*this));
}

// destructor:
PointLight::~PointLight(void) {}

// assignemnt operator:
PointLight&
PointLight::operator= (const PointLight& rhs) {

	if (this == &rhs)
		return *this;

	Light::operator=(rhs);
	ls = rhs.ls;
	color = rhs.color;
	location = rhs.location;
	da = rhs.da;

	return *this;
}

Vector3D
PointLight::get_direction(ShadeRec& sr) {
	return (location - sr.hit_point).hat();
}

RGBColor
PointLight::L(ShadeRec& sr) {
	return (ls * color).powc(1 / da);
}

bool
PointLight::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	
	double t;
	int num_objects = sr.w.objects.size();
	double  d = location.distance(ray.o);

	for (int i = 0; i < num_objects; i++) {
		if (sr.w.objects[i]->shadow_hit(ray, t) && t < d)
			return true;
	}

	return false;
}