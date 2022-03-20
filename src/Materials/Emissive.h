#pragma once

#include "Material.h"

class Emissive : public Material {

public:

	// default constructor
	Emissive(); 

	// copy constructor
	Emissive(const Emissive& rhs); 

	// clone
	virtual Emissive* clone() const;

	// assignment operator
	Emissive& operator= (const Emissive& rhs);

	// set light intensity
	void set_ls(const double c);

	// set light greyscale color
	void set_ce(const double c);

	// set light color by component
	void set_ce(const double r, const double g, const double b);

	// set light color by reference
	void set_ce(const RGBColor col);

	RGBColor get_Le(ShadeRec& sr) const;

	RGBColor shade(ShadeRec& sr) const;

	RGBColor area_light_shade(ShadeRec& sr) const;

	RGBColor path_shade(ShadeRec& sr) const;

	RGBColor global_shade(ShadeRec& sr) const;

private:

	// light intensity
	double ls; 

	// light color
	RGBColor ce; 
};

inline void
Emissive::set_ls(const double c) 
{
	ls = c;
}

inline void
Emissive::set_ce(const double c) 
{
	ce = RGBColor(c);
}

inline void
Emissive::set_ce(const double r, const double g, const double b) 
{
	ce = RGBColor(r, g, b);
}

inline void
Emissive::set_ce(const RGBColor col) 
{
	ce = col;
}

inline RGBColor
Emissive::get_Le(ShadeRec& sr) const 
{
	return ls * ce;
}