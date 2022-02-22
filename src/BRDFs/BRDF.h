#pragma once

#include "../Samplers/Sampler.h"
#include "../Samplers/MultiJittered.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/RGBColor.h"

class BRDF {

public:

	BRDF(void); // default constructor

	BRDF(const BRDF& rhs); // copy constructor

	virtual BRDF*
		clone(void) const = 0;

	virtual // destructor
		~BRDF(); 

	BRDF& // assignment operator
		operator= (const BRDF& rhs);

	// setters

	void
		set_sampler(Sampler* sp);

	void
		set_samples(const int& n);

	//functions

	virtual RGBColor
		f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const = 0;

	virtual RGBColor
		sample_f(const ShadeRec& sr, Vector3D& w_i, const Vector3D& w_o) const = 0;

	virtual RGBColor
		rho(const ShadeRec& sr, const Vector3D& w_o) const = 0;

protected:

	Sampler* sampler_ptr;
};

inline void
BRDF::set_sampler(Sampler* sp) {
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_hemisphere(1); // for perfect diffuse 
}

inline void
BRDF::set_samples(const int& n) {
	sampler_ptr = new MultiJittered(n);
	sampler_ptr->map_samples_to_hemisphere(1); // for perfect diffuse
}