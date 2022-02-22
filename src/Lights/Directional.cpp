#include "Directional.h"

// default constructor
Directional::Directional(void)
	: Light(),
	ls(1.0),
	color(1.0),
	direction(0, 1, 0)
{}

// copy constructor
Directional::Directional(const Directional& dl)
	: Light(dl),
	ls(dl.ls),
	color(dl.color),
	direction(dl.direction)
{}

// assignment operator
Directional&
Directional::operator= (const Directional& rhs) {
	if (this == &rhs)
		return *this;

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;
	direction = rhs.direction;

	return *this;
}

// destructor
Directional::~Directional(void) {}

Vector3D
Directional::get_direction(ShadeRec& sr) {
	return direction;
}

RGBColor
Directional::L(ShadeRec& s) {
	return (ls * color);
}
