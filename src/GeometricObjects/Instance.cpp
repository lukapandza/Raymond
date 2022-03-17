#include "Instance.h"
#include <math.h>

Matrix_4
Instance::forward_matrix;

Instance::Instance(void) 
	: GeometricObject(),
	object_ptr(NULL),
	inv_matrix(),
	bbox(),
	transform_the_texture(true) {
	forward_matrix.set_identity();
}

Instance::Instance(GeometricObject* obj_ptr) 
	: GeometricObject(),
	object_ptr(obj_ptr),
	inv_matrix(),
	bbox(),
	transform_the_texture(true) {
	forward_matrix.set_identity();
	if (obj_ptr->get_material())
		this->material_ptr = obj_ptr->get_material();
}

Instance::Instance(const Instance& rhs) 
	: GeometricObject(rhs),
	inv_matrix(rhs.inv_matrix),
	transform_the_texture(rhs.transform_the_texture) {
	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();
	else  object_ptr = NULL;
}

Instance*
Instance::clone(void) const {
	return new Instance(*this);
}

Instance::~Instance(void) {
	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}
}

Instance&
Instance::operator=(const Instance& rhs) {
	
	if (this == &rhs)
		return *this;

	GeometricObject::operator=(rhs);

	if (object_ptr) {
		delete object_ptr;
		object_ptr = NULL;
	}

	if (rhs.object_ptr)
		object_ptr = rhs.object_ptr->clone();
	else
		object_ptr = NULL;

	inv_matrix = rhs.inv_matrix;
	bbox = rhs.bbox;
	transform_the_texture = rhs.transform_the_texture;

	return *this;
}

void
Instance::set_object(GeometricObject* obj_ptr) {
	object_ptr = obj_ptr;
}

BBox
Instance::get_bounding_box(void) {
	return bbox;
}

Material*
Instance::get_material(void) const {
	return material_ptr;
}

void
Instance::set_material(Material* materialPtr) {
	material_ptr = materialPtr;
}

bool
Instance::hit(const Ray& raymond, double& tmin, ShadeRec& sr) const {
	
	// inverse ray is created by applying the inverse matrix to raymond. 

	if (object_ptr->hit(Ray(this->inv_matrix * raymond.o, this->inv_matrix * raymond.d), tmin, sr)) {
		
		sr.normal = this->inv_matrix * sr.normal;
		sr.normal.normalize();

		//sr.material_ptr = this->material_ptr;
		if (this->object_ptr->get_material())
			this->material_ptr = this->object_ptr->get_material();

		if (!transform_the_texture)
			sr.local_hit_point = raymond.o + tmin * raymond.d;

		return true;
	}

	return false;
}

bool
Instance::shadow_hit(const Ray& raymond, double& tmin) const {

	// inverse ray is created by applying the inverse matrix to raymond. 

	return object_ptr->shadow_hit(Ray(this->inv_matrix * raymond.o, this->inv_matrix * raymond.d), tmin);
}

void
Instance::translate(const Vector3D& trans) {

	Matrix_4 inv_translation_matrix;				// temporary inverse translation matrix	

	inv_translation_matrix.m[0][3] = -trans.x;
	inv_translation_matrix.m[1][3] = -trans.y;
	inv_translation_matrix.m[2][3] = -trans.z;

	inv_matrix = inv_matrix * inv_translation_matrix;

	Matrix_4 translation_matrix;					// temporary translation matrix	

	translation_matrix.m[0][3] = trans.x;
	translation_matrix.m[1][3] = trans.y;
	translation_matrix.m[2][3] = trans.z;

	forward_matrix = translation_matrix * forward_matrix;
}

void
Instance::translate(const double dx, const double dy, const double dz) {

	Matrix_4 inv_translation_matrix;				// temporary inverse translation matrix	

	inv_translation_matrix.m[0][3] = -dx;
	inv_translation_matrix.m[1][3] = -dy;
	inv_translation_matrix.m[2][3] = -dz;

	inv_matrix = inv_matrix * inv_translation_matrix;

	Matrix_4 translation_matrix;					// temporary translation matrix	

	translation_matrix.m[0][3] = dx;
	translation_matrix.m[1][3] = dy;
	translation_matrix.m[2][3] = dz;

	forward_matrix = translation_matrix * forward_matrix;
}

void
Instance::scale(const Vector3D& s) {

	Matrix_4	inv_scaling_matrix;			// temporary inverse scaling matrix

	inv_scaling_matrix.m[0][0] = 1.0 / s.x;
	inv_scaling_matrix.m[1][1] = 1.0 / s.y;
	inv_scaling_matrix.m[2][2] = 1.0 / s.z;

	inv_matrix = inv_matrix * inv_scaling_matrix;

	Matrix_4	scaling_matrix;				// temporary scaling matrix

	scaling_matrix.m[0][0] = s.x;
	scaling_matrix.m[1][1] = s.y;
	scaling_matrix.m[2][2] = s.z;

	forward_matrix = scaling_matrix * forward_matrix;
}

void
Instance::scale(const double a, const double b, const double c) {

	Matrix_4 inv_scaling_matrix;					// temporary inverse scaling matrix

	inv_scaling_matrix.m[0][0] = 1.0 / a;
	inv_scaling_matrix.m[1][1] = 1.0 / b;
	inv_scaling_matrix.m[2][2] = 1.0 / c;

	inv_matrix = inv_matrix * inv_scaling_matrix;

	Matrix_4 scaling_matrix;						// temporary scaling matrix

	scaling_matrix.m[0][0] = a;
	scaling_matrix.m[1][1] = b;
	scaling_matrix.m[2][2] = c;

	forward_matrix = scaling_matrix * forward_matrix;
}

void
Instance::rotate_x(const double theta) {

	double sin_theta = sin(theta * PI_ON_180);
	double cos_theta = cos(theta * PI_ON_180);

	Matrix_4 inv_x_rotation_matrix;					// temporary inverse rotation matrix about x axis

	inv_x_rotation_matrix.m[1][1] = cos_theta;
	inv_x_rotation_matrix.m[1][2] = sin_theta;
	inv_x_rotation_matrix.m[2][1] = -sin_theta;
	inv_x_rotation_matrix.m[2][2] = cos_theta;

	inv_matrix = inv_matrix * inv_x_rotation_matrix;

	Matrix_4 x_rotation_matrix;						// temporary rotation matrix about x axis

	x_rotation_matrix.m[1][1] = cos_theta;
	x_rotation_matrix.m[1][2] = -sin_theta;
	x_rotation_matrix.m[2][1] = sin_theta;
	x_rotation_matrix.m[2][2] = cos_theta;

	forward_matrix = x_rotation_matrix * forward_matrix;
}

void
Instance::rotate_y(const double theta) {

	double sin_theta = sin(theta * PI_ON_180);
	double cos_theta = cos(theta * PI_ON_180);

	Matrix_4 inv_y_rotation_matrix;					// temporary inverse rotation matrix about y axis

	inv_y_rotation_matrix.m[0][0] = cos_theta;
	inv_y_rotation_matrix.m[0][2] = -sin_theta;
	inv_y_rotation_matrix.m[2][0] = sin_theta;
	inv_y_rotation_matrix.m[2][2] = cos_theta;

	inv_matrix = inv_matrix * inv_y_rotation_matrix;

	Matrix_4 y_rotation_matrix;						// temporary rotation matrix about x axis

	y_rotation_matrix.m[0][0] = cos_theta;
	y_rotation_matrix.m[0][2] = sin_theta;
	y_rotation_matrix.m[2][0] = -sin_theta;
	y_rotation_matrix.m[2][2] = cos_theta;

	forward_matrix = y_rotation_matrix * forward_matrix;
}

void
Instance::rotate_z(const double theta) {
	double sin_theta = sin(theta * PI_ON_180);
	double cos_theta = cos(theta * PI_ON_180);

	Matrix_4 inv_z_rotation_matrix;					// temporary inverse rotation matrix about y axis	

	inv_z_rotation_matrix.m[0][0] = cos_theta;
	inv_z_rotation_matrix.m[0][1] = sin_theta;
	inv_z_rotation_matrix.m[1][0] = -sin_theta;
	inv_z_rotation_matrix.m[1][1] = cos_theta;

	inv_matrix = inv_matrix * inv_z_rotation_matrix;

	Matrix_4 z_rotation_matrix;						// temporary rotation matrix about y axis

	z_rotation_matrix.m[0][0] = cos_theta;
	z_rotation_matrix.m[0][1] = -sin_theta;
	z_rotation_matrix.m[1][0] = sin_theta;
	z_rotation_matrix.m[1][1] = cos_theta;

	forward_matrix = z_rotation_matrix * forward_matrix;
}

void
Instance::shear(const Matrix_4& s) {

	Matrix_4 inverse_shearing_matrix;    // inverse shear matrix

	// discriminant

	double d = 1.0 - s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2] - s.m[2][1] * s.m[1][2]
		+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];

	// diagonals

	inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	inverse_shearing_matrix.m[3][3] = d;

	// first row

	inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

	// second row

	inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

	// third row

	inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2];

	// divide by discriminant

	inverse_shearing_matrix = inverse_shearing_matrix / d;

	inv_matrix = inv_matrix * inverse_shearing_matrix;

	forward_matrix = s * forward_matrix;
}
