#pragma once

#include "GeometricObject.h"
#include "../Samplers/Sampler.h"

class RectangleObject : public GeometricObject {

public:

	RectangleObject(void);

	RectangleObject(const double c_x, const double c_y, const double c_z, const double a_x, const double a_y, const double a_z, const double b_x, const double b_y, const double b_z, const double n_x, const double n_y, const double n_z);

	RectangleObject(const RectangleObject& rhs);

	RectangleObject*
		clone(void) const;

	RectangleObject&
		operator=(const RectangleObject& rhs);

	~RectangleObject(void);

	bool
		hit(const Ray& raymond, double& tmin, ShadeRec& s) const;

	bool
		shadow_hit(const Ray& raymond, double& tmin) const;

	void
		set_sampler(Sampler* sampler);

	Point3D 
		sample(void);

	double
		pdf(ShadeRec& sr);

	Normal
		get_normal(const Point3D& p);

private:

	Point3D 		corner;   		// corner vertex 
	Vector3D		a;				// side
	Vector3D		b;				// side
	double			a_len_squared;	// square of the length of side a
	double			b_len_squared;	// square of the length of side b
	Normal			normal;

	Sampler*		sampler_ptr;
	double			inv_area;
};

inline void
RectangleObject::set_sampler(Sampler* sampler) {
	sampler_ptr = sampler;
}

inline double
RectangleObject::pdf(ShadeRec& sr) {
	return inv_area;
}

inline Normal
RectangleObject::get_normal(const Point3D& p) {
	return normal;
}