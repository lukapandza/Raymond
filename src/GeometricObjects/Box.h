#pragma once

#include "GeometricObject.h"

class Box : public GeometricObject {

	// this is an axis-aligned box
	// affine transforms must be applied to make it not axis aligned

public:

	// default constructor
	Box(); 

	// component constructor
	Box(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1);

	// points constructor
	Box(const Point3D c0, const Point3D c1);

	// copy constructor
	Box(const Box& rhs); 

	// clone
	Box* clone() const;

	// assignment operator
	Box& operator=(const Box& rhs);

	// intersects ray with box
	bool hit(const Ray& raymond, double& t, ShadeRec& s) const;

	// intersects a shadow ray with box
	bool shadow_hit(const Ray& raymond, double& t) const;

	// returns normal at hit point
	Normal get_normal(const int& face_hit) const;

private:

	// component
	double x0, y0, z0, x1, y1, z1;
};