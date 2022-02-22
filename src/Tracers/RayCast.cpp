#include "RayCast.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"
#include "../Materials/Material.h"

// default constructor
RayCast::RayCast(void) 
	: Tracer()
{}

// world ptr constructor
RayCast::RayCast(World* _worldPtr) 
	: Tracer(_worldPtr)
{}

// destructor
RayCast::~RayCast() {}

RGBColor
RayCast::trace_ray(const Ray& raymond, const int& depth) const {
	
	ShadeRec sr(world_ptr->hit_objects(raymond)); // copy constructor
	
	if (sr.hit_an_object) {
		sr.ray = raymond; // for specular reflection (Chapter 15)
		return (sr.material_ptr->shade(sr));
	}
	else
		return (world_ptr->background_color);
}