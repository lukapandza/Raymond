#pragma once

#include "Ray.h"
#include "Point3D.h"

class BBox {

public:

	// member variables:
	double x0, y0, z0, x1, y1, z1;

	BBox(); // default constructor

	BBox(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1); // raw constructor

	BBox(const Point3D _c0, const Point3D _c1); // points constructor

	BBox(const BBox& rhs); // copy constructor

	BBox& operator=(const BBox& rhs); // assignment operator

	~BBox(); // destructor

	// methods:

	bool hit(const Ray& raymond) const;

	bool inside(const Point3D& p) const;
};
