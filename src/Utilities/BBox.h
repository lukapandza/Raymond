#pragma once

#include "Ray.h"
#include "Point3D.h"

class BBox {

public:

	double x0, y0, z0, x1, y1, z1;

	BBox(void); // default constructor

	BBox(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1);

	BBox(const Point3D c0, const Point3D c1);

	BBox(const BBox& rhs); // copy constructor

	BBox&
		operator=(const BBox& rhs);

	~BBox(void);

	bool
		hit(const Ray& raymond) const;

	bool
		inside(const Point3D& p) const;

};
