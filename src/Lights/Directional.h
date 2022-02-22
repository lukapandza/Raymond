#pragma once

#include "Light.h"
#include "../Utilities/Point3D.h"

class Directional : public Light {

public:

	Directional(void); // default constructor

	Directional(const Directional& rhs); // copy constructor

	virtual Directional*
		clone(void) const = 0;

	virtual
		~Directional(); // destructor

	Directional& // assignment operator
		operator= (const Directional& rhs);

	// setters:

	void
		set_intensity(const double  a);

	void
		set_color(const double  a);

	void
		set_color(const double  r, const double  g, const double  b);

	void
		set_color(const RGBColor& col);

	void
		set_direction(const double  x, const double  y, const double  z);

	void
		set_direction(const Vector3D& v);

	// functions:

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual RGBColor
		L(ShadeRec& sr);

private:

	double  ls; // light intensity
	RGBColor color; // light color
	Vector3D direction; // direction the light comes from
};

// inlined functions:

inline void
Directional::set_intensity(const double  a) {
	ls = a;
}

inline void
Directional::set_color(const double  a) {
	color = RGBColor(a);
}

inline void
Directional::set_color(const double  r, const double  g, const double  b) {
	color = RGBColor(r, g, b);
}

inline void
Directional::set_color(const RGBColor& col) {
	color = col;
}

inline void
Directional::set_direction(const double  x, const double  y, const double  z) {
	direction = Vector3D(x, y, z);
	direction.normalize();
}

inline void
Directional::set_direction(const Vector3D& v) {
	direction = v;
	direction.normalize();
}

