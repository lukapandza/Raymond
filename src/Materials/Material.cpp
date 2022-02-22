#include "Material.h"
#include "../Utilities/Constants.h"
#include "../Utilities/ShadeRec.h"

// default constructor
Material::Material(void) {}

// copy constructor
Material::Material(const Material& rhs) {}

// destructor
Material::~Material(void) {}

// assignment operator
Material&
Material::operator=(const Material& rhs) {
	return *this;
}

RGBColor
Material::shade(ShadeRec& sr) {
	return black;
}

RGBColor
Material::area_light_shade(ShadeRec& sr) {
	return black;
}

RGBColor
Material::path_shade(ShadeRec& sr) {
	return black;
}

RGBColor
Material::global_shade(ShadeRec& sr) {
	return black;
}

RGBColor
Material::get_Le(ShadeRec& sr) const {
	return black;
}