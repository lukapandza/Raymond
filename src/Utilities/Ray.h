#pragma once

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:
	
	// ray origin
	Point3D	o;

	// ray direction
	Vector3D d;
	
	// default constructor
	Ray();			
	
	// point-vector constructor
	Ray(const Point3D& origin, const Vector3D& dir);	
	
	// copy constructor
	Ray(const Ray& ray); 		
	
	// assignment operator
	Ray& operator= (const Ray& rhs);
};
