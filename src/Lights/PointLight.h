#pragma once

#include "Light.h"
#include "../Utilities/Point3D.h"

class PointLight : public Light {

public:

	PointLight(void); // default constructor

	PointLight(const PointLight& rhs); // copy constructor

	virtual PointLight*
		clone(void) const;

	virtual
		~PointLight(); // destructor

	PointLight& // assignment operator
		operator= (const PointLight& rhs);

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
		set_location(const double  x, const double  y, const double  z);

	void
		set_location(const Point3D& p);

	void
		set_da_power(const double  a);

	// functions:

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual RGBColor
		L(ShadeRec& sr);

	bool
		in_shadow(const Ray& ray, const ShadeRec& sr) const;

private:

	double  ls; // light intensity
	RGBColor color; // light color
	Point3D location; // light location
	double  da; // distance attenuation power
};

// inlined functions:

inline void
PointLight::set_intensity(const double  a) {
	ls = a;
}

inline void
PointLight::set_color(const double  a) {
	color = RGBColor(a);
}

inline void
PointLight::set_color(const double  r, const double  g, const double  b) {
	color = RGBColor(r, g, b);
}

inline void
PointLight::set_color(const RGBColor& col) {
	color = col;
}

inline void
PointLight::set_location(const double  x, const double  y, const double  z) {
	location = Point3D(x, y, z);
}

inline void
PointLight::set_location(const Point3D& p) { 
	location = p;
}

inline void
PointLight::set_da_power(const double  a) {
	da = a;
}