#pragma once

#include "Phong.h"
#include "../BRDFs/FresnelReflector.h"
#include "../BTDFs/FresnelTransmitter.h"

class Dielectric : public Phong {

public:

	// default constructor
	Dielectric();

	// copy constructor
	Dielectric(const Dielectric& rhs);

	// clone
	Dielectric* clone() const;

	// destructor
	~Dielectric();

	// assignment operator
	Dielectric& operator= (const Dielectric& rhs);

	void set_cf_in(const RGBColor c) { cf_in = c; }

	void set_cf_out(const RGBColor c) { cf_out = c; }

	void set_ior_in(const double ior) { fresnel_brdf->set_ior_in(ior); fresnel_btdf->set_ior_in(ior); }

	void set_ior_out(const double ior) { fresnel_brdf->set_ior_out(ior); fresnel_btdf->set_ior_out(ior); }

	RGBColor shade(ShadeRec& sr) const;

	RGBColor area_light_shade(ShadeRec& sr) const { return RGBColor(0, 0, 0); }

	RGBColor path_shade(ShadeRec& sr) const { return RGBColor(0, 0, 0); }

	RGBColor global_shade(ShadeRec& sr) const { return RGBColor(0, 0, 0); }

private:

	// interior filter color
	RGBColor cf_in; 

	// exterior filter color
	RGBColor cf_out; 

	FresnelReflector* fresnel_brdf;
	FresnelTransmitter* fresnel_btdf;

};