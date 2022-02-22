#include "Light.h"
#include "../Utilities/Constants.h"

// default constructor:
Light::Light(void) 
	: shadows(true)
{}

// copy constructor:
Light::Light(const Light& rhs) 
	: shadows(rhs.shadows)
{}

// destructor:
Light::~Light(void) {}

// assignment operator:
Light&
Light::operator=(const Light& rhs) {
	
	if (this == &rhs)
		return *this;

	shadows = rhs.shadows;

	return *this;
}

RGBColor
Light::L(ShadeRec& sr) {
	return black;
}
