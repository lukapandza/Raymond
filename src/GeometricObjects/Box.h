#pragma once

#include "GeometricObject.h"

class Box : public GeometricObject {

public:

	Box(void); // default constructor

	Box(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1);

	Box(const Point3D c0, const Point3D c1);

	Box(const Box& rhs); // copy constructor

	Box*
		clone(void) const;

	Box&
		operator=(const Box& rhs);

	~Box(void);

	bool
		hit(const Ray& raymond, double& t, ShadeRec& s) const;

	bool
		shadow_hit(const Ray& raymond, double& t) const;

	Normal
		get_normal(const int& face_hit) const;

private:

	double x0, y0, z0, x1, y1, z1;
};