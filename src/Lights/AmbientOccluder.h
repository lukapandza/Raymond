#pragma once

#include "Light.h"
#include "../Samplers/Sampler.h"

class AmbientOccluder : public Light {

public:

	AmbientOccluder(void); // default constructor

	AmbientOccluder(const AmbientOccluder& rhs); // copy constructor

	virtual AmbientOccluder*
		clone(void) const;

	virtual
		~AmbientOccluder(); // destructor

	AmbientOccluder& //assignment operator
		operator= (const AmbientOccluder& rhs);

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
		set_min(const double  c);

	void
		set_min(const double  r, const double  g, const double  b);

	void
		set_min(const RGBColor& col);

	// functions:

	void
		set_sampler(Sampler* s_ptr);

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual bool
		in_shadow(const Ray& raymond, const ShadeRec& sr) const;

	virtual RGBColor
		L(ShadeRec& sr);

private:

	double  ls; // light intensity
	RGBColor color; // light color

	Vector3D u, v, w;
	Sampler* sampler_ptr;
	RGBColor min_amount;
};

inline void
AmbientOccluder::set_intensity(const double  a) {
	ls = a;
}

inline void
AmbientOccluder::set_color(const double  a) {
	color = RGBColor(a);
}

inline void
AmbientOccluder::set_color(const double  r, const double  g, const double  b) {
	color = RGBColor(r, g, b);
}

inline void
AmbientOccluder::set_color(const RGBColor& col) {
	color = col;
}

inline void
AmbientOccluder::set_min(const double  c) {
	min_amount = RGBColor(c);
}

inline void
AmbientOccluder::set_min(const double  r, const double  g, const double  b) {
	min_amount = RGBColor(r, g, b);
}

inline void
AmbientOccluder::set_min(const RGBColor& col) {
	min_amount = col;
}