#include "Disk.h"

Disk::Disk(void) 
	: center(0, 0, 0),
	radius(1.0),
	normal(0, 1, 0),
	r_squared(1.0)
{}

Disk::Disk(const double c_x, const double c_y, const double c_z, const double r, const double n_x, const double n_y, const double n_z) 
	: center(c_x, c_y, c_z),
	radius(r),
	normal(n_x, n_y, n_z),
	r_squared(r * r)
{}

Disk::Disk(const Disk& rhs) 
	: GeometricObject(rhs),
	center(rhs.center),
	radius(rhs.radius),
	normal(rhs.normal),
	r_squared(rhs.r_squared)
{}

Disk*
Disk::clone() const 
{
	return new Disk(*this);
}

Disk&
Disk::operator=(const Disk& rhs) 
{
	if (this == &rhs)
		return *this;

	center = rhs.center;
	radius = rhs.radius;
	normal = rhs.normal;
	r_squared = rhs.r_squared;

	return *this;
}

bool
Disk::hit(const Ray& raymond, double& t_min, ShadeRec& s) const 
{
	double t = (center - raymond.o) * normal / (raymond.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = raymond.o + t * raymond.d;

	if (center.d_squared(p) < r_squared) {
		t_min = t;
		s.normal = normal;
		s.local_hit_point = p;
		return true;
	}
	else
		return false;
}

bool
Disk::shadow_hit(const Ray& raymond, double& t_min) const 
{
	double t = (center - raymond.o) * normal / (raymond.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = raymond.o + t * raymond.d;

	if (center.d_squared(p) < r_squared) {
		t_min = t;
		return true;
	}
	else
		return false;
}
