#pragma once

#include "GeometricObject.h"
#include "../Utilities/Matrix_4.h"
#include "../Utilities/BBox.h"

class Instance : public GeometricObject {
	
public:

	// default constructor
	Instance();

	// object constructor
	Instance(GeometricObject* obj_ptr);

	// copy constructor
	Instance(const Instance& rhs);

	// clone
	Instance* clone() const;

	// destructor
	~Instance();

	// assignment operator
	Instance& operator= (const Instance& rhs);

	// object pointer setter
	void set_object(GeometricObject* obj_ptr);

	// set texture transform bool
	void transform_texture(const bool transform);

	// returns transformed objects bounding box
	BBox get_bounding_box() const;

	// return material pointer
	Material* get_material() const;

	// set instance material
	void set_material(Material* materialPtr);

	// intersect ray with instance
	bool hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	// intersect shadow ray with instance
	bool shadow_hit(const Ray& raymond, double& tmin) const;

	Point3D sample();

	double pdf(ShadeRec& sr);

	Normal get_normal(const Point3D& p);

	Matrix_4 get_forward_matrix() const;

	// affine tranformation functions:

	void translate(const Vector3D& trans);

	void translate(const double dx, const double dy, const double dz);

	void scale(const Vector3D& s);

	void scale(const double a, const double b, const double c);

	// rotation argument in degrees
	void rotate_x(const double r);

	// rotation argument in degrees
	void rotate_y(const double r);

	// rotation argument in degrees
	void rotate_z(const double r);

	void shear(const Matrix_4& m);

private:

	// object to be transformed
	GeometricObject* object_ptr; 

	// inverse transformation matrix
	Matrix_4 inv_matrix; 

	// transformation matrix
	static Matrix_4 forward_matrix; 

	// transformed object's bounding box
	BBox bbox; 

	// do we transform the texture?
	bool transform_the_texture;	
};

inline void
Instance::set_object(GeometricObject* obj_ptr)
{
	object_ptr = obj_ptr;
}

inline void
Instance::transform_texture(const bool transform) 
{
	transform_the_texture = transform;
}

inline BBox
Instance::get_bounding_box() const
{
	return bbox;
}

inline Material*
Instance::get_material() const
{
	return material_ptr;
}

inline void
Instance::set_material(Material* materialPtr)
{
	material_ptr = materialPtr;
}

inline Point3D
Instance::sample() 
{
	return object_ptr->sample();
}

inline double
Instance::pdf(ShadeRec& sr) 
{
	return object_ptr->pdf(sr);
}

inline Normal
Instance::get_normal(const Point3D& p) 
{
	return object_ptr->get_normal(p);
}

inline Matrix_4
Instance::get_forward_matrix() const
{
	return this->forward_matrix;
}
