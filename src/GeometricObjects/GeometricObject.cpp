#include "../Utilities/Constants.h"
#include "GeometricObject.h"

GeometricObject::GeometricObject()
	: material_ptr(nullptr),
	bbox(0, 0, 0, 0, 0, 0)
{}

GeometricObject::GeometricObject(const GeometricObject& object)
	: material_ptr(object.material_ptr),
	bbox(object.bbox)
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

	this->bbox = rhs.bbox;

	return *this;
}

GeometricObject::~GeometricObject()
{
	if (this->material_ptr)
		delete this->material_ptr;
}

void
GeometricObject::set_material(Material* mat_ptr) 
{
	material_ptr = mat_ptr;
}
