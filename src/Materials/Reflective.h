#pragma once

#include "Phong.h"
#include "../BRDFs/PerfectSpecular.h"

class Reflective : public Phong {

public:

	// default constructor
	Reflective();

	// copy constructor
	Reflective(const Reflective& rhs);

	// clone
	Reflective* clone() const;

	// destructor
	~Reflective();

	// assignment operator
	Reflective& operator= (const Reflective& rhs);

	// set reflection intensity
	void set_kr(const double c);

	// set greyscale reflection color
	void set_cr(const double c);

	// set reflection color by component
	void set_cr(const double r, const double g, const double b);

	// set reflection color by reference
	void set_cr(const RGBColor& col);

	RGBColor shade(ShadeRec& sr) const ;

	RGBColor area_light_shade(ShadeRec& sr) const ;

	RGBColor path_shade(ShadeRec& sr) const ;

	RGBColor global_shade(ShadeRec& sr) const ;

private:

	PerfectSpecular* reflective_brdf;
};

inline void
Reflective::set_kr(const double c) 
{
	reflective_brdf->set_kr(c);
}

inline void
Reflective::set_cr(const double c) 
{
	reflective_brdf->set_cr(c);
}

inline void
Reflective::set_cr(const double r, const double g, const double b) 
{
	reflective_brdf->set_cr(r, g, b);
}

inline void
Reflective::set_cr(const RGBColor& col) 
{
	reflective_brdf->set_cr(col);
}
