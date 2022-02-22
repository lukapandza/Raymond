#pragma once

#include "GeometricObject.h"

class Triangle : public GeometricObject {

public:

	Point3D v0, v1, v2;
	Normal normal;

	Triangle(void);

	Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2);

	Triangle(const double v0_x, const double v0_y, const double v0_z, const double v1_x, const double v1_y, const double v1_z, const double v2_x, const double v2_y, const double v2_z);

	Triangle(const Triangle& rhs);

	Triangle*
		clone(void) const;

	Triangle&
		operator=(const Triangle& rhs);

	~Triangle(void);

	bool
		hit(const Ray& raymond, double& tmin, ShadeRec& s) const;

	bool
		shadow_hit(const Ray& raymond, double& tmin) const;
};