#pragma once

#include "Ray.h"
#include "Point3D.h"

class BBox {

public:

	// member variable
	double x0, y0, z0, x1, y1, z1;

	// default constructor
	BBox();

	// raw value constructor
	BBox(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1);

	// points constructor
	BBox(const Point3D _c0, const Point3D _c1);

	// copy constructor
	BBox(const BBox& rhs); 

	// assignment operator
	BBox& operator=(const BBox& rhs);

	// intersect object with Ray
	bool hit(const Ray& raymond) const;

	// is a point inside the bounding box
	bool inside(const Point3D& p) const;
};
