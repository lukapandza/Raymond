#pragma once

#include "../Samplers/Sampler.h"
#include "../Samplers/Regular.h"
#include "../Samplers/MultiJittered.h"

//-------------------------------------------------------------------------------------- class ViewPlane

class ViewPlane {
	public:
		int 			hres;   					// horizontal image resolution 
		int 			vres;   					// vertical image resolution
		double			s;							// pixel size
		
		double			gamma;						// gamma correction factor
		double			inv_gamma;					// the inverse of the gamma correction factor
		bool			show_out_of_gamut;			// display red if RGBColor out of gamut

		int				num_samples;
		Sampler*		sampler_ptr;

		int				max_depth;

		double			half_hres;					// avoid divide by 2 in pinhole camera
		double			half_vres;					// avoid divide by 2 in pinhole camera
		
									
	
	public:
	
		ViewPlane();   								// default Constructor
				
		ViewPlane(const ViewPlane& vp);				// copy constructor

		ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator
		
		~ViewPlane();   							// destructor
						
		void 													
		set_hres(const int h_res);
		
		void 													
		set_vres(const int v_res);
				
		void
		set_pixel_size(const double size);
		
		void
		set_gamma(const double g);
		
		void
		set_gamut_display(const bool show);

		void
		set_sampler(Sampler* sampler);

		void
		set_samples(const int n);

		void
		set_max_depth(const int n);
};




// ------------------------------------------------------------------------------ set_hres

inline void 													
ViewPlane::set_hres(const int h_res) {
	hres = h_res;
	half_hres = (double)hres * 0.5;
}


// ------------------------------------------------------------------------------ set_vres

inline void 													
ViewPlane::set_vres(const int v_res) {
	vres = v_res;
	half_vres = (double)vres * 0.5;
}


// ------------------------------------------------------------------------------ set_pixel_size

inline void 													
ViewPlane::set_pixel_size(const double size) {
	s = size;
}


// ------------------------------------------------------------------------------ set_gamma

inline void
ViewPlane::set_gamma(const double g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}


// ------------------------------------------------------------------------------ set_gamut_display

inline void
ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}

inline void
ViewPlane::set_max_depth(const int n) {
	max_depth = n;
}
