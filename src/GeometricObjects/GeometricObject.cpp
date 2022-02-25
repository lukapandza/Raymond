// this file contains the definition of the class GeometricObject 

#include "../Utilities/Constants.h"
#include "GeometricObject.h"


// ---------------------------------------------------------------------- default constructor

GeometricObject::GeometricObject(void)
	: 	color(black),
	material_ptr(nullptr)
{}


// ---------------------------------------------------------------------- copy constructor

GeometricObject::GeometricObject (const GeometricObject& object)
	: 	color(object.color),
	material_ptr(object.material_ptr)
{}	


// ---------------------------------------------------------------------- assignment operator

GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) {
	
	if (this == &rhs)
		return (*this);
		
	color = rhs.color;

	return (*this);
}


// ---------------------------------------------------------------------- destructor

GeometricObject::~GeometricObject (void) {}

void
GeometricObject::set_material(Material* mat_ptr) {
	material_ptr = mat_ptr;
}

Material*
GeometricObject::get_material(void) const {
	return material_ptr;
}
