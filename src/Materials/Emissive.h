#pragma once

#include "Material.h"

class Emissive : public Material {

public:

	Emissive(void); // default constructor

	Emissive(const Emissive& rhs); // copy constructor

	virtual Emissive*
		clone(void) const;

	virtual // destructor
		~Emissive();

	Emissive& // assignment operator
		operator= (const Emissive& rhs);

	// setters:

	void
		set_ls(const double  c);

	void
		set_ce(const double  c);

	void
		set_ce(const double  r, const double  g, const double  b);

	void
		set_ce(const RGBColor col);

	// functions:

	virtual RGBColor
		get_Le(ShadeRec& sr) const;

	virtual RGBColor
		shade(ShadeRec& sr);

	virtual RGBColor
		area_light_shade(ShadeRec& sr);

	virtual RGBColor
		path_shade(ShadeRec& sr);

	virtual RGBColor
		global_shade(ShadeRec& sr);

private:

	double  ls; // radiance scaling factor
	RGBColor ce; // color
};

// inlined functions:

inline void
Emissive::set_ls(const double  c) {
	ls = c;
}

inline void
Emissive::set_ce(const double  c) {
	ce = RGBColor(c);
}

inline void
Emissive::set_ce(const double  r, const double  g, const double  b) {
	ce = RGBColor(r, g, b);
}

inline void
Emissive::set_ce(const RGBColor col) {
	ce = col;
}

inline RGBColor
Emissive::get_Le(ShadeRec& sr) const {
	return ls * ce;
}