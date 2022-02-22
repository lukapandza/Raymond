#pragma once
// this file contains the declaration of the class GeometricObject

#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

#include "../Utilities/Constants.h"
					

class GeometricObject {	
	
	public:	

		GeometricObject(void);									// default constructor
		
		GeometricObject(const GeometricObject& object);			// copy constructor
	
		virtual GeometricObject*								// virtual copy constructor
		clone(void) const = 0;

		virtual 												// destructor
		~GeometricObject (void);	
			
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

		virtual bool
			shadow_hit(const Ray& raymond, double& tmin) const;

		virtual void 							// This needs to be virtual so that it can be overridden in Compound
			set_material(Material* mPtr); 			// It therefore shouldn't be inlined

		Material*
			get_material(void) const;

		// used for area lighting:

		virtual Point3D
			sample(void);

		virtual double
			pdf(ShadeRec& sr);

		virtual Normal
			get_normal(const Point3D& p);
		

		// the following three functions are only required for Chapter 3
		
		void
		set_color(const RGBColor& c);
				
		void
		set_color(const double r, const double g, const double b);
		
		RGBColor
		get_color(void);

	
	protected:
	
		mutable Material* material_ptr;
		RGBColor   color;						// only used for Bare Bones ray tracing
	
		GeometricObject&						// assignment operator
		operator= (const GeometricObject& rhs);
};


// --------------------------------------------------------------------  set_colour

inline void
GeometricObject::set_color(const RGBColor& c) {
	color = c;
}

// --------------------------------------------------------------------  set_colour

inline void 
GeometricObject::set_color(const double r, const double g, const double b) {
	color.r = r;
	color.b = b;
	color.g = g;
}

// --------------------------------------------------------------------  get_colour

inline RGBColor 
GeometricObject::get_color(void) {
	return (color);
}

inline bool
GeometricObject::shadow_hit(const Ray& raymond, double& tmin) const {
	return false;
}

inline Point3D
GeometricObject::sample(void) {
	return (Point3D(0.0));
}

inline double
GeometricObject::pdf(ShadeRec& sr) {
	return (0.0);
}

inline Normal
GeometricObject::get_normal(const Point3D& p) {
	return (Normal());
}
