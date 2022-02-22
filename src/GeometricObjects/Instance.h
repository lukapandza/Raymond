#pragma once

#include "GeometricObject.h"
#include "../Utilities/Matrix_4.h"
#include "../Utilities/BBox.h"

class Instance : public GeometricObject {
	
public:

	Instance(void);

	Instance(GeometricObject* obj_ptr);

	Instance(const Instance& rhs);

	Instance*
		clone(void) const;

	~Instance(void);

	Instance&
		operator= (const Instance& rhs);

	void
		set_object(GeometricObject* obj_ptr);

	void
		transform_texture(const bool transform);

	BBox
		get_bounding_box(void);

	Material*
		get_material(void) const;

	void
		set_material(Material* materialPtr);

	bool
		hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	bool
		shadow_hit(const Ray& raymond, double& tmin) const;

	virtual Point3D
		sample(void);

	virtual double
		pdf(ShadeRec& sr);

	virtual Normal
		get_normal(const Point3D& p);

	// affine tranformation functions

	void
		translate(const Vector3D& trans);

	void
		translate(const double dx, const double dy, const double dz);

	void
		scale(const Vector3D& s);

	void
		scale(const double a, const double b, const double c);

	virtual void
		rotate_x(const double r);

	virtual void
		rotate_y(const double r);

	virtual void
		rotate_z(const double r);

	void
		shear(const Matrix_4& m);

private:

	GeometricObject* object_ptr; // object to be transformed
	Matrix_4 inv_matrix; // inverse transformation matrix
	static 	Matrix_4 forward_matrix; // transformation matrix
	BBox bbox; // transformed object's bounding box
	bool transform_the_texture;	// do we transform the texture?
};

inline void
Instance::transform_texture(const bool transform) {
	transform_the_texture = transform;
}

inline Point3D
Instance::sample(void) {
	return object_ptr->sample();
}

inline double
Instance::pdf(ShadeRec& sr) {
	return object_ptr->pdf(sr);
}

inline Normal
Instance::get_normal(const Point3D& p) {
	return object_ptr->get_normal(p);
}