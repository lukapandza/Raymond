#pragma once

// This file contains the declaration of the class Sphere

#include "GeometricObject.h"
#include "../Samplers/Sampler.h"

//-------------------------------------------------------------------------------- class Sphere

class Sphere: public GeometricObject {	
								  	
	public:
		
		Sphere(void);   									// Default constructor
				
		Sphere(Point3D center, double r);					// Constructor 
					
		Sphere(const Sphere& sphere); 						// Copy constructor
		
		virtual Sphere* 									// Virtual copy constructor
		clone(void) const;

		virtual												// Destructor
		~Sphere(void);   									

		Sphere& 											// assignment operator
		operator= (const Sphere& sphere);				
																					
		void
		set_center(const Point3D& c);
		
		void
		set_center(const double x, const double y, const double z);
		
		void
		set_radius(const double r);
						
		virtual bool 												 
		hit(const Ray& ray, double& t, ShadeRec& s) const;	

		virtual bool
			shadow_hit(const Ray& ray, double& tmin) const;

		void
			set_sampler(Sampler* sampler);

		Point3D
			sample(void);

		double
			pdf(ShadeRec& sr);

		virtual Normal
			get_normal(const Point3D& p);
		
	protected:
	
		Point3D 	center;   			// center coordinates as a point  
		double 		radius;				// the radius 
		
		static const double kEpsilon;   // for shadows and secondary rays

		Sampler* sampler_ptr;
		double inv_area;
};



inline void
Sphere::set_center(const Point3D& c) {
	center = c;
}
		
inline void
Sphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
Sphere::set_radius(const double r) {
	radius = r;
}

inline void
Sphere::set_sampler(Sampler* sampler) {
	sampler_ptr = sampler;
	sampler_ptr->map_samples_to_unit_sphere();
}

inline Point3D
Sphere::sample(void) {
	Point3D sp = sampler_ptr->sample_unit_sphere();
	return (center + radius * sp);
}

inline double
Sphere::pdf(ShadeRec& sr) {
	return inv_area;
}

inline Normal
Sphere::get_normal(const Point3D& p) {
	Normal n = p - center;
	n.normalize();
	return n;
}

class ConcaveSphere : public Sphere {
	
public:
	ConcaveSphere() : Sphere() {}

	~ConcaveSphere() { Sphere::~Sphere(); }

	Normal
		get_normal(const Point3D& p);

	bool
		hit(const Ray& ray, double& t, ShadeRec& s) const;
};

inline Normal
ConcaveSphere::get_normal(const Point3D& p) {
	Normal n = this->center - p;
	n.normalize();
	return n;
}
