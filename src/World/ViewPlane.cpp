// This file contains the definition the ViewPlane class

#include "ViewPlane.h"
	
// ---------------------------------------------------------------- default constructor	
						
ViewPlane::ViewPlane(void)
	: hres(400),
	vres(400),
	s(1.0),
	gamma(1.0),
	inv_gamma(1.0),
	show_out_of_gamut(false),
	num_samples(1),
	sampler_ptr(NULL),
	max_depth(0),
	half_hres(200.0),
	half_vres(200.0)
{}


// ---------------------------------------------------------------- copy constructor

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
		show_out_of_gamut(vp.show_out_of_gamut),
		num_samples(vp.num_samples),
		sampler_ptr(vp.sampler_ptr),
		max_depth(vp.max_depth),
		half_hres(vp.half_hres),
		half_vres(vp.half_vres)
{}


// ---------------------------------------------------------------- assignment operator

ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return (*this);
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;
	num_samples			= rhs.num_samples;
	sampler_ptr			= rhs.sampler_ptr;
	max_depth			= rhs.max_depth;
	
	return (*this);
}


// -------------------------------------------------------------- destructor

ViewPlane::~ViewPlane(void) {}

//set_sampler:
void
ViewPlane::set_sampler(Sampler* sp) {
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
}

//set_samples:
void
ViewPlane::set_samples(const int n) {
	num_samples = n;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (num_samples > 1)
		sampler_ptr = new MultiJittered(num_samples);
	else
		sampler_ptr = new Regular(1);
}
