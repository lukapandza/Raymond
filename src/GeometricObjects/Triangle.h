#pragma once

#include "GeometricObject.h"

class Triangle : public GeometricObject {

public:

	// vertex
	Point3D v0, v1, v2;

	// normal
	Normal normal;

	// default constructor
	Triangle();

	// point constructor
	Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2);

	// component constructor
	Triangle(const double v0_x, const double v0_y, const double v0_z, const double v1_x, const double v1_y, const double v1_z, const double v2_x, const double v2_y, const double v2_z);

	// copy constructor
	Triangle(const Triangle& rhs);

	// clone
	Triangle* clone() const;

	// assignment operator
	Triangle& operator=(const Triangle& rhs);

	// intersect ray with triangle
	bool hit(const Ray& raymond, double& tmin, ShadeRec& s) const;

	// intersect shadow ray with traingle
	bool shadow_hit(const Ray& raymond, double& tmin) const;
};
