#include "Sphere.h"
#include "math.h"
#include "../Utilities/Constants.h"
					
Sphere::Sphere()	
	: GeometricObject(),
	center(Point3D(0, 0, 0)),
	radius(1.0),
	sampler_ptr(nullptr),
	inv_area(4 * PI)
{}

Sphere::Sphere(Point3D c, double r)
	: GeometricObject(),
	center(c),
	radius(r),
	sampler_ptr(nullptr),
	inv_area(4 * PI * r * r)
{}

Sphere* 
Sphere::clone() const 
{
	return new Sphere(*this);
}

Sphere::Sphere (const Sphere& sphere)
	: GeometricObject(sphere),
	center(sphere.center),
	radius(sphere.radius),
	sampler_ptr(sphere.sampler_ptr),
	inv_area(sphere.inv_area)
{}

Sphere& 
Sphere::operator= (const Sphere& rhs)		
{
	if (this == &rhs)
		return *this;

	GeometricObject::operator= (rhs);

	center 	= rhs.center;
	radius	= rhs.radius;
	sampler_ptr = rhs.sampler_ptr;
	inv_area = rhs.inv_area;

	return *this;
}

Sphere::~Sphere() 
{
	delete sampler_ptr;
}

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	Vector3D	temp 	= ray.o - center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0) // no real solutions
		return false;

	else {	
		double e = sqrt(disc);
		double inv_denom = 1.0 / (2.0 * a);
		double t = (-b - e) * inv_denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		} 
	
		t = (-b + e) * inv_denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal = (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		} 
	}
	return false;
}

bool
Sphere::shadow_hit(const Ray& ray, double& tmin) const 
{
	Vector3D	temp = ray.o - center;
	double 		a = ray.d * ray.d;
	double 		b = 2.0 * temp * ray.d;
	double 		c = temp * temp - radius * radius;
	double 		disc = b * b - 4.0 * a * c;

	if (disc < 0.0) // no real solutions
		return false;

	else {
		double e = sqrt(disc);
		double inv_denom = 1.0 / (2.0 * a);
		double t = (-b - e) * inv_denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			return true;
		}

		t = (-b + e) * inv_denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			return true;
		}
	}
	return false;
}

bool
ConcaveSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	bool did_hit = Sphere::hit(ray, tmin, sr);

	if (did_hit)
		sr.normal = -sr.normal;

	return did_hit;
}







