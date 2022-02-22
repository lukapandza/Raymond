#include "BBox.h"
#include "Constants.h"

BBox::BBox(void)
	: x0(-1), y0(-1), z0(-1),
	x1(1), y1(1), z1(1)
{}

BBox::BBox(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1) 
	: x0(_x0), y0(_y0), z0(_z0),
	x1(_x1), y1(_y1), z1(_z1)
{}

BBox::BBox(const Point3D c0, const Point3D c1) 
	: x0(c0.x), y0(c0.y), z0(c0.z),
	x1(c1.x), y1(c1.y), z1(c1.z)
{}

BBox::BBox(const BBox& rhs) 
	: x0(rhs.x0), y0(rhs.y0), z0(rhs.z0),
	x1(rhs.x1), y1(rhs.y1), z1(rhs.z1)
{}

BBox&
BBox::operator= (const BBox& rhs) {

	if (this == &rhs)
		return *this;

	x0 = rhs.x0;
	y0 = rhs.y0;
	z0 = rhs.z0;

	x1 = rhs.x1;
	y1 = rhs.y1;
	z1 = rhs.z1;

	return *this;
}

BBox::~BBox(void) {}

bool
BBox::hit(const Ray& raymond) const {

	double o_x = raymond.o.x;
	double o_y = raymond.o.y;
	double o_z = raymond.o.z;

	double d_x = raymond.d.x;
	double d_y = raymond.d.y;
	double d_z = raymond.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / d_x;
	if (a >= 0) {
		tx_min = (x0 - o_x) * a;
		tx_max = (x1 - o_x) * a;
	}
	else {
		tx_min = (x1 - o_x) * a;
		tx_max = (x0 - o_x) * a;
	}

	double b = 1.0 / d_y;
	if (b >= 0) {
		ty_min = (y0 - o_y) * b;
		ty_max = (y1 - o_y) * b;
	}
	else {
		ty_min = (y1 - o_y) * b;
		ty_max = (y0 - o_y) * b;
	}

	double c = 1.0 / d_z;
	if (c >= 0) {
		tz_min = (z0 - o_z) * c;
		tz_max = (z1 - o_z) * c;
	}
	else {
		tz_min = (z1 - o_z) * c;
		tz_max = (z0 - o_z) * c;
	}

	double t0, t1;

	// find largest entering t value

	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	// find smallest exiting t value

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	return (t0 < t1 && t1 > kEpsilon);
}

bool
BBox::inside(const Point3D& p) const {
	return ((p.x > x0 && p.x < x1) && (p.y > y0 && p.y < y1) && (p.z > z0 && p.z < z1));
};
