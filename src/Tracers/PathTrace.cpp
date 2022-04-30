#include "PathTrace.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"
#include "../Materials/Material.h"

// default constructor
PathTrace::PathTrace(void)
	: Tracer()
{}

// world ptr constructor
PathTrace::PathTrace(World* _worldPtr)
	: Tracer(_worldPtr)
{}

// destructor
PathTrace::~PathTrace() {}

RGBColor
PathTrace::trace_ray(const Ray& raymond, const int& depth) const {

	if (depth > world_ptr->vp.max_depth)
		return black;
	else {

		ShadeRec sr(world_ptr->hit_objects(raymond)); // copy constructor

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = raymond; // for specular reflection (Chapter 15)

			return sr.material_ptr->path_shade(sr);
		}
		else
			return world_ptr->background_color;
	}
}

RGBColor
PathTrace::trace_ray(const Ray& raymond, double& tmin, const int& depth) const
{
	if (depth > world_ptr->vp.max_depth)
		return black;
	else {

		ShadeRec sr(world_ptr->hit_objects(raymond)); // copy constructor

		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = raymond; // for specular reflection (Chapter 15)
			tmin = sr.t;

			return sr.material_ptr->path_shade(sr);
		}
		else {
			tmin = kHugeValue;
			return world_ptr->background_color;
		}
	}
}
