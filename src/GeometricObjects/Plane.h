#pragma once

#include "GeometricObject.h"

class Plane: public GeometricObject {
	
public:
	
	// default constructor
	Plane();   												
	
	// point, normal constructor	
	Plane(const Point3D& point, const Normal& normal);			
	
	// copy constructor
	Plane(const Plane& plane); 									
	
	// clone
	Plane* clone() const;

	// assignment operator
	Plane& operator= (const Plane& rhs);							
	
	// intersect ray with plane
	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
	// intersect shadow ray with plane
	bool shadow_hit(const Ray& raymond, double& tmin) const;

private:

	// point through which plane passes 
	Point3D a;

	// normal to the plane
	Normal n;
};
