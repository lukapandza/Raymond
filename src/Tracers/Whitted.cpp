#include "Whitted.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"
#include "../Materials/Material.h"

// default constructor
Whitted::Whitted(void)
	: Tracer()
{}

// world ptr constructor
Whitted::Whitted(World* _worldPtr)
	: Tracer(_worldPtr)
{}

// destructor
Whitted::~Whitted() {}

RGBColor
Whitted::trace_ray(const Ray& raymond, const int& depth) const {

	if (depth > world_ptr->vp.max_depth)
		return black;
	else {
		
		ShadeRec sr(world_ptr->hit_objects(raymond)); // copy constructor

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = raymond; // for specular reflection (Chapter 15)
			
			return sr.material_ptr->shade(sr);
		}
		else
			return world_ptr->background_color;
	}
}