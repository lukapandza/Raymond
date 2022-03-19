#include "Box.h"

Box::Box()
	: x0(-1), y0(-1), z0(-1),
	x1(1), y1(1), z1(1)
{}

Box::Box(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1)
	: x0(_x0), y0(_y0), z0(_z0),
	x1(_x1), y1(_y1), z1(_z1)
{}

Box::Box(const Point3D c0, const Point3D c1)
	: x0(c0.x), y0(c0.y), z0(c0.z),
	x1(c1.x), y1(c1.y), z1(c1.z)
{}

Box::Box(const Box& rhs)
	: x0(rhs.x0), y0(rhs.y0), z0(rhs.z0),
	x1(rhs.x1), y1(rhs.y1), z1(rhs.z1)
{}

Box*
Box::clone() const 
{
	return new Box(*this);
}

Box&
Box::operator= (const Box& rhs) 
{
	if (this == &rhs)
		return *this;

	x0 = rhs.x0; y0 = rhs.y0; z0 = rhs.z0;
	x1 = rhs.x1; y1 = rhs.y1; z1 = rhs.z1;

	return *this;
}

bool
Box::hit(const Ray& raymond, double& t, ShadeRec& s) const 
{
	double a = 1.0 / raymond.d.x;
	double b = 1.0 / raymond.d.y;
	double c = 1.0 / raymond.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	if (a >= 0) {
		tx_min = (x0 - raymond.o.x) * a;
		tx_max = (x1 - raymond.o.x) * a;
	}
	else {
		tx_min = (x1 - raymond.o.x) * a;
		tx_max = (x0 - raymond.o.x) * a;
	}

	if (b >= 0) {
		ty_min = (y0 - raymond.o.y) * b;
		ty_max = (y1 - raymond.o.y) * b;
	}
	else {
		ty_min = (y1 - raymond.o.y) * b;
		ty_max = (y0 - raymond.o.y) * b;
	}

	if (c >= 0) {
		tz_min = (z0 - raymond.o.z) * c;
		tz_max = (z1 - raymond.o.z) * c;
	}
	else {
		tz_min = (z1 - raymond.o.z) * c;
		tz_max = (z0 - raymond.o.z) * c;
	}

	double t0, t1;
	int face_in, face_out;

	// find largest entering t value
	if (tx_min > ty_min) {
		t0 = tx_min;
		face_in = (a >= 0.0) ? 0 : 3;
	}
	else {
		t0 = ty_min;
		face_in = (b >= 0.0) ? 1 : 4;
	}

	if (tz_min > t0) {
		t0 = tz_min;
		face_in = (c >= 0.0) ? 2 : 5;
	}

	// find smallest exiting t value
	if (tx_max < ty_max) {
		t1 = tx_max;
		face_out = (a >= 0.0) ? 3 : 0;
	}
	else {
		t1 = ty_max;
		face_out = (b >= 0.0) ? 4 : 1;
	}

	if (tz_max < t1) {
		t1 = tz_max;
		face_out = (c >= 0.0) ? 5 : 2;
	}
	

	if (t0 < t1 && t1 > kEpsilon) { // condition for a hit
		
		if (t0 > kEpsilon) {
			t = t0; // ray hits outside surface
			s.normal = get_normal(face_in);
		}
		else {
			t = t1; // ray hits inside surface
			s.normal = get_normal(face_out);
		}

		s.local_hit_point = raymond.o + t * raymond.d;
		return true;
	}
	else
		return false;
}

bool
Box::shadow_hit(const Ray& raymond, double& t) const 
{
	double a = 1.0 / raymond.d.x;
	double b = 1.0 / raymond.d.y;
	double c = 1.0 / raymond.d.z;

	double d_x = raymond.d.x;
	double d_y = raymond.d.y;
	double d_z = raymond.d.z;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	if (a >= 0) {
		tx_min = (x0 - raymond.o.x) * a;
		tx_max = (x1 - raymond.o.x) * a;
	}
	else {
		tx_min = (x1 - raymond.o.x) * a;
		tx_max = (x0 - raymond.o.x) * a;
	}

	if (b >= 0) {
		ty_min = (y0 - raymond.o.y) * b;
		ty_max = (y1 - raymond.o.y) * b;
	}
	else {
		ty_min = (y1 - raymond.o.y) * b;
		ty_max = (y0 - raymond.o.y) * b;
	}

	if (c >= 0) {
		tz_min = (z0 - raymond.o.z) * c;
		tz_max = (z1 - raymond.o.z) * c;
	}
	else {
		tz_min = (z1 - raymond.o.z) * c;
		tz_max = (z0 - raymond.o.z) * c;
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

	if (t0 < t1 && t1 > kEpsilon) { // condition for a hit

		if (t0 > kEpsilon)
			t = t0; // ray hits outside surface
		else
			t = t1; // ray hits inside surface

		return true;
	}
	else
		return false;
}

inline Normal
Box::get_normal(const int& face_hit) const 
{
	switch (face_hit) {
		case 0: return (Normal(-1, 0, 0));	// -x face
		case 1: return (Normal(0, -1, 0));	// -y face
		case 2: return (Normal(0, 0, -1));	// -z face
		case 3: return (Normal(1, 0, 0));	// +x face
		case 4: return (Normal(0, 1, 0));	// +y face
		default: return (Normal(0, 0, 1));	// +z face
	}
}
