#include "../Utilities/Constants.h"
#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: material_ptr(nullptr)
{}

GeometricObject::GeometricObject (const GeometricObject& object)
	: material_ptr(object.material_ptr)
{}	

GeometricObject&														
GeometricObject::operator= (const GeometricObject& rhs) 
{
	if (this == &rhs)
		return *this;

	if (rhs.material_ptr)
		this->material_ptr = rhs.material_ptr->clone();
	else
		this->material_ptr = nullptr;

	return *this;
}

GeometricObject::~GeometricObject () 
{
}

void
GeometricObject::set_material(Material* mat_ptr) 
{
	material_ptr = mat_ptr;
}
