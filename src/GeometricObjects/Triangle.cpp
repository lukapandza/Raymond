#include "Triangle.h"

Triangle::Triangle(void) 
	: v0(0, 0, 0), 
	v1(0, 0, 1), 
	v2(1, 0, 0),
	normal(0, 1, 0)
{}

Triangle::Triangle(const Point3D& _v0, const Point3D& _v1, const Point3D& _v2) 
	: v0(_v0),
	v1(_v1),
	v2(_v2) {
	
	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}

Triangle::Triangle(const double v0_x, const double v0_y, const double v0_z, const double v1_x, const double v1_y, const double v1_z, const double v2_x, const double v2_y, const double v2_z) 
	: v0(v0_x, v0_y, v0_z),
	v1(v1_x, v1_y, v1_z),
	v2(v2_x, v2_y, v2_z) {

	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}

Triangle::Triangle(const Triangle& rhs) 
	: v0(rhs.v0),
	v1(rhs.v1),
	v2(rhs.v2),
	normal(rhs.normal)
{}

Triangle*
Triangle::clone(void) const {
	return new Triangle(*this);
}

Triangle&
Triangle::operator=(const Triangle& rhs) {
		
	if (this == &rhs)
		return *this;

	v0 = rhs.v0;
	v1 = rhs.v1;
	v2 = rhs.v2;
	normal = rhs.normal;

	return *this;
}

Triangle::~Triangle(void) {}

bool
Triangle::hit(const Ray& raymond, double& tmin, ShadeRec& sr) const {

	double a = v0.x - v1.x;
	double b = v0.x - v2.x;
	double c = raymond.d.x;
	double d = v0.x - raymond.o.x;

	double e = v0.y - v1.y;
	double f = v0.y - v2.y;
	double g = raymond.d.y;
	double h = v0.y - raymond.o.y;

	double i = v0.z - v1.z;
	double j = v0.z - v2.z;
	double k = raymond.d.z;
	double l = v0.z - raymond.o.z;

	double m = f * k - g * j;
	double n = h * k - g * l;
	double p = f * l - h * j;
	double q = g * i - e * k;
	double s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return false;

	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return false;

	if (beta + gamma >= 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return false;

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = raymond.o + t * raymond.d;

	return true;
}

bool
Triangle::shadow_hit(const Ray& raymond, double& tmin) const {

	double a = v0.x - v1.x;
	double b = v0.x - v2.x;
	double c = raymond.d.x;
	double d = v0.x - raymond.o.x;

	double e = v0.y - v1.y;
	double f = v0.y - v2.y;
	double g = raymond.d.y;
	double h = v0.y - raymond.o.y;

	double i = v0.z - v1.z;
	double j = v0.z - v2.z;
	double k = raymond.d.z;
	double l = v0.z - raymond.o.z;

	double m = f * k - g * j;
	double n = h * k - g * l;
	double p = f * l - h * j;
	double q = g * i - e * k;
	double s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return false;

	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return false;

	if (beta + gamma >= 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon)
		return false;

	tmin = t;

	return true;
}
