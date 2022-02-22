#pragma once

#include "Light.h"

class Ambient : public Light{

public:

	Ambient(void); // default constructor

	Ambient(const Ambient& rhs); // copy constructor

	virtual Ambient*
		clone(void) const;

	virtual
		~Ambient(); // destructor

	Ambient& // assignment operator
		operator= (const Ambient& rhs);

	// setters:

	void
		set_intensity(const double  a);

	void
		set_color(const double  a);

	void
		set_color(const double  r, const double  g, const double  b);

	void
		set_color(const RGBColor& col);

	// functions:

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual RGBColor
		L(ShadeRec& sr);

private:

	double  ls; // light intensity
	RGBColor color; // light color
};

// inlined functions:

inline void
Ambient::set_intensity(const double  a) {
	ls = a;
}

inline void 
Ambient::set_color(const double  a) {
	color = RGBColor(a);
}

inline void
Ambient::set_color(const double  r, const double  g, const double  b) {
	color = RGBColor(r, g, b);
}

inline void
Ambient::set_color(const RGBColor& col) {
	color = col;
}