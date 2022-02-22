#include "Ambient.h"

// default constructor:
Ambient::Ambient(void) 
	: Light(),
	ls(1.0),
	color(1.0)
{}

// copy constructor:
Ambient::Ambient(const Ambient& rhs)
	: Light(rhs),
	ls(rhs.ls),
	color(rhs.color)
{}

// clone
Ambient*
Ambient::clone(void) const {
	return (new Ambient(*this));
}

// destructor:
Ambient::~Ambient(void) {}

// assignemnt operator:
Ambient&
Ambient::operator= (const Ambient& rhs) {
	
	if (this == &rhs)
		return *this;

	Light::operator=(rhs);
	ls = rhs.ls;
	color = rhs.color;

	return *this;
}

Vector3D
Ambient::get_direction(ShadeRec& sr) {
	return (Vector3D(0.0)); //nullvec
}

RGBColor
Ambient::L(ShadeRec& sr) {
	return (ls * color);
}