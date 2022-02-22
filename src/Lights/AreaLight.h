#pragma once

#include "Light.h"
#include "../GeometricObjects/GeometricObject.h"

class AreaLight : public Light {

public:

	AreaLight(void);

	AreaLight(const AreaLight& rhs);

	AreaLight*
		clone(void) const;

	~AreaLight(void);

	AreaLight&
		operator=(const AreaLight& rhs);

	void
		set_object(GeometricObject* obj_ptr);

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual bool
		in_shadow(const Ray& ray, const ShadeRec& sr) const;
	
	virtual RGBColor
		L(ShadeRec& sr);
	
	virtual double 
		G(const ShadeRec& sr) const;
	
	virtual double 
		pdf(ShadeRec& sr) const;

private:

	GeometricObject* object_ptr;
	Material* material_ptr;
	Point3D sample_point;
	Normal light_normal;
	Vector3D w_i;
};

inline void
AreaLight::set_object(GeometricObject* obj_ptr) {
	object_ptr = obj_ptr;
	material_ptr = object_ptr->get_material();
}