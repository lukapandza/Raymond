#include "Emissive.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Constants.h"

Emissive::Emissive()
	: Material(),
	ls(1),
	ce(1, 1, 1)
{}

Emissive::Emissive(const Emissive& rhs)
	: Material(rhs),
	ls(rhs.ls),
	ce(rhs.ce)
{}

Emissive*
Emissive::clone() const 
{
	return new Emissive(*this);
}

// assignment operator
Emissive&
Emissive::operator=(const Emissive& rhs) 
{
	if (this == &rhs)
		return *this;

	Material::operator=(rhs);

	ls = rhs.ls; ce = rhs.ce;

	return *this;
}

RGBColor
Emissive::shade(ShadeRec& sr) const 
{
	if (-sr.normal * sr.ray.d > 0.0)
		return sr.depth == 0 ? ce : ls * ce; // for anti aliasing when ls >> 1.0
	else
		return black;
}

RGBColor
Emissive::area_light_shade(ShadeRec& sr) const 
{
	if (-sr.normal * sr.ray.d > 0.0)
		return sr.depth == 0 ? ce : ls * ce; // for anti aliasing when ls >> 1.0
	else
		return black;
}

RGBColor
Emissive::path_shade(ShadeRec& sr) const 
{
	if (-sr.normal * sr.ray.d > 0.0)
		return sr.depth == 0 ? ce : ls * ce; // for anti aliasing when ls >> 1.0
	else
		return black;
}

RGBColor
Emissive::global_shade(ShadeRec& sr) const 
{
	if (sr.depth == 1)
		return black;

	if (-sr.normal * sr.ray.d > 0.0)
		return sr.depth == 0 ? ce : ls * ce; // for anti aliasing when ls >> 1.0
	else
		return black;
}
