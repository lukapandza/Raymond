#pragma once

#include "GeometricObject.h"
#include "../Samplers/Sampler.h"

class RectangleObject : public GeometricObject {

public:

	// default constructor
	RectangleObject();

	// component constructor
	RectangleObject(const double c_x, const double c_y, const double c_z, const double a_x, const double a_y, const double a_z, const double b_x, const double b_y, const double b_z, const double n_x, const double n_y, const double n_z);

	// copy constructor
	RectangleObject(const RectangleObject& rhs);

	// clone
	RectangleObject* clone() const;

	// assignment operator
	RectangleObject& operator=(const RectangleObject& rhs);

	// destructor
	~RectangleObject();

	// intersect ray with rectangle
	bool hit(const Ray& raymond, double& tmin, ShadeRec& s) const;

	// intersect shadow ray with rectangle
	bool shadow_hit(const Ray& raymond, double& tmin) const;

	// set sampler pointer
	void set_sampler(Sampler* sampler);

	Point3D sample();

	double pdf(ShadeRec& sr);

	Normal get_normal(const Point3D& p);

private:

	// corner vertex
	Point3D corner;
	
	// side
	Vector3D a, b;

	// square of the length of side
	double a_len_squared, b_len_squared;

	// rect normal
	Normal normal;

	Sampler* sampler_ptr;
	double inv_area;
};

inline void
RectangleObject::set_sampler(Sampler* sampler) 
{
	sampler_ptr = sampler;
}

inline double
RectangleObject::pdf(ShadeRec& sr) 
{
	return inv_area;
}

inline Normal
RectangleObject::get_normal(const Point3D& p) 
{
	return normal;
}