#pragma once

#include "../Utilities/RGBColor.h"
#include "../Utilities/Constants.h"
class ShadeRec; // forward decleration

class Material {

public:

	// defualt constructor
	Material() {}

	// copy constructor
	Material(const Material& rhs) {}

	// clone
	virtual Material* clone() const = 0;

	// assignment operator
	virtual Material& operator= (const Material& rhs) { return *this; }

	// functions:

	// RayCast shading
	virtual RGBColor shade(ShadeRec& sr) const { return black; }

	// AreaLighting shading
	virtual RGBColor area_light_shade(ShadeRec& sr) const { return black; }

	// PathTrace shading
	virtual RGBColor path_shade(ShadeRec& sr) const { return black; }

	// GlobalTrace shading
	virtual RGBColor global_shade(ShadeRec& sr) const { return black; }

	// for emissive materials
	virtual RGBColor get_Le(ShadeRec& sr) const { return black; }

};