#include "Cylinder.h"

Cylinder::Cylinder()
	: y_0(0), y_1(1), r(1)
{}

Cylinder::Cylinder(const double y_0, const double y_1, const double r)
	: y_0(y_0), y_1(y_1), r(r)
{}

Cylinder::Cylinder(const Cylinder& rhs)
	: y_0(rhs.y_0), y_1(rhs.y_1), r(rhs.r)
{}

Cylinder* 
Cylinder::clone() const
{
	return new Cylinder(*this);
}

Cylinder&
Cylinder::operator=(const Cylinder& rhs) 
{
	if (this == &rhs)
		return *this;

	y_0 = rhs.y_0; y_1 = rhs.y_1; r = rhs.r;

	return *this;
}

bool
Cylinder::hit(const Ray& raymond, double& tmin, ShadeRec& sr) const
{
	double a = raymond.d.x * raymond.d.x + raymond.d.z * raymond.d.z;
	double b = 2.0 * (raymond.o.x * raymond.d.x + raymond.o.z * raymond.d.z);
	double c = raymond.o.x * raymond.o.x + raymond.o.z * raymond.o.z - r * r;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0)
		return false;

	double sq_disc = sqrt(disc);

	double t = (-b - sq_disc) / (2.0 * a); // smaller root

	if (t > kEpsilon) {
		Point3D hitpoint = raymond.o + raymond.d * t;

		if (hitpoint.y > y_0 && hitpoint.y < y_1) {
			tmin = t;
			sr.normal = Normal(hitpoint.x / r, 0.0, hitpoint.z / r);

			if (-raymond.d * sr.normal < 0.0) 
				sr.normal = -sr.normal;

			sr.local_hit_point = hitpoint;

			return true;
		}
	}

	t = (-b + sq_disc) / (2.0 * a); // bigger root

	if (t > kEpsilon) {
		Point3D hitpoint = raymond.o + raymond.d * t;

		if (hitpoint.y > y_0 && hitpoint.y < y_1) {
			tmin = t;
			sr.normal = Normal(hitpoint.x / r, 0.0, hitpoint.z / r);

			if (-raymond.d * sr.normal < 0.0)
				sr.normal = -sr.normal;

			sr.local_hit_point = hitpoint;

			return true;
		}
	}

	return false;
}

bool
Cylinder::shadow_hit(const Ray& raymond, double& tmin) const
{
	double a = raymond.d.x * raymond.d.x + raymond.d.z * raymond.d.z;
	double b = 2.0 * (raymond.o.x * raymond.d.x + raymond.o.z * raymond.d.z);
	double c = raymond.o.x * raymond.o.x + raymond.o.z * raymond.o.z - r * r;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0)
		return false;

	double sq_disc = sqrt(disc);

	double t = (-b - sq_disc) / (2.0 * a); // smaller root

	if (t > kEpsilon) {
		Point3D hitpoint = raymond.o + raymond.d * t;

		if (hitpoint.y > y_0 && hitpoint.y < y_1) {
			tmin = t;
			return true;
		}
	}

	t = (-b + sq_disc) / (2.0 * a); // bigger root

	if (t > kEpsilon) {
		Point3D hitpoint = raymond.o + raymond.d * t;

		if (hitpoint.y > y_0 && hitpoint.y < y_1) {
			tmin = t;
			return true;
		}
	}

	return false;
}
