#include "RectangleObject.h"

RectangleObject::RectangleObject(void)
	: corner(0, 0, 0),
	a(1, 0, 0),
	b(0, 1, 0),
	a_len_squared(1.0),
	b_len_squared(1.0),
	normal(0, 0, 1),
	inv_area(1.0),
	sampler_ptr(NULL)
{}

RectangleObject::RectangleObject(const double c_x, const double c_y, const double c_z, const double a_x, const double a_y, const double a_z, const double b_x, const double b_y, const double b_z, const double n_x, const double n_y, const double n_z) 
	: corner(c_x, c_y, c_z),
	a(a_x, a_y, a_z),
	b(b_x, b_y, b_z),
	a_len_squared(a.len_squared()),
	b_len_squared(b.len_squared()),
	normal(n_x, n_y, n_z),
	inv_area(1.0 / (a.length() * b.length())),
	sampler_ptr(NULL)
{}

RectangleObject::RectangleObject(const RectangleObject& rhs) 
	: corner(rhs.corner),
	a(rhs.a),
	b(rhs.b),
	a_len_squared(rhs.a_len_squared),
	b_len_squared(rhs.b_len_squared),
	normal(rhs.normal),
	inv_area(rhs.inv_area),
	sampler_ptr(rhs.sampler_ptr)
{}

RectangleObject*
RectangleObject::clone(void) const {
	return new RectangleObject(*this);
}

RectangleObject&
RectangleObject::operator=(const RectangleObject& rhs) {
	
	if (this == &rhs)
		return *this;

	corner = rhs.corner;
	a = rhs.a;
	b = rhs.b;
	a_len_squared = rhs.a_len_squared;
	b_len_squared = rhs.b_len_squared;
	normal = rhs.normal;
	inv_area = rhs.inv_area;
	sampler_ptr = rhs.sampler_ptr;
}

RectangleObject::~RectangleObject(void) {}

bool
RectangleObject::hit(const Ray& raymond, double& tmin, ShadeRec& s) const {

	double t = (corner - raymond.o) * normal / (raymond.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = raymond.o + t * raymond.d;
	Vector3D d = p - corner;

	double d_dot_a = d * a;

	if (d_dot_a < 0.0 || d_dot_a > a_len_squared)
		return false;

	double d_dot_b = d * b;

	if (d_dot_b < 0.0 || d_dot_b > b_len_squared)
		return false;

	tmin = t;
	s.normal = normal;
	s.local_hit_point = p;

	return true;
}

bool
RectangleObject::shadow_hit(const Ray& raymond, double& tmin) const {

	double t = (corner - raymond.o) * normal / (raymond.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = raymond.o + t * raymond.d;
	Vector3D d = p - corner;

	double d_dot_a = d * a;

	if (d_dot_a < 0.0 || d_dot_a > a_len_squared)
		return false;

	double d_dot_b = d * b;

	if (d_dot_b < 0.0 || d_dot_b > b_len_squared)
		return false;

	tmin = t;

	return true;
}

Point3D
RectangleObject::sample(void) {
	Point2D sp = sampler_ptr->sample_unit_square();
	return (corner + sp.x * a + sp.y * b);
}
