#pragma once

#include "../Samplers/Sampler.h"
#include "../Samplers/MultiJittered.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/RGBColor.h"

class BRDF {

public:

	// default constructor
	BRDF(); 

	// copy constructor
	BRDF(const BRDF& rhs); 

	// clone
	virtual BRDF* clone() const = 0;

	// destructor
	virtual ~BRDF(); 

	// assignment operator
	BRDF& operator= (const BRDF& rhs);

	// sampler assignment
	void set_sampler(Sampler* sp);

	// Multijittered(n) sampler assignment
	void set_samples(const int& n);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& w_o) const;

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