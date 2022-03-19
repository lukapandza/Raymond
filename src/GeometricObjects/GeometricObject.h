#pragma once

#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeRec.h"

#include "../Utilities/Constants.h"
					

class GeometricObject {	
	
public:	

	// default constructor
	GeometricObject();
		
	// copy constructor
	GeometricObject(const GeometricObject& object);

	// assignment operator
	GeometricObject& operator= (const GeometricObject& rhs);
	
	// clone
	virtual GeometricObject* clone() const = 0;

	// destructor
	virtual ~GeometricObject ();	
	
	// intersect ray with object
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

	// intersect shadow ray with object
	virtual bool shadow_hit(const Ray& raymond, double& tmin) const;

	// assign material to object
	virtual void set_material(Material* mPtr); // must be virtual for Compund override. Cant' be inlined

	// get pointer to objects material
	Material* get_material() const;

	// used for area lighting:

	virtual Point3D sample();

	virtual double pdf(ShadeRec& sr);

	virtual Normal get_normal(const Point3D& p);
	
protected:
	
	mutable Material* material_ptr;
};

inline bool
GeometricObject::shadow_hit(const Ray& raymond, double& tmin) const
{
	return false;
}

inline Point3D
GeometricObject::sample() 
{
	return Point3D(0.0);
}

inline double
GeometricObject::pdf(ShadeRec& sr) 
{
	return 0.0;
}

inline Normal
GeometricObject::get_normal(const Point3D& p) 
{
	return Normal();
}

inline Material*
GeometricObject::get_material() const
{
	return this->material_ptr;
}
