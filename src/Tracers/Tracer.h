// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#pragma once

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/RGBColor.h"

class World;

class Tracer {
public:
	
	Tracer(void); // default constructor
		
	Tracer(World* _world_ptr); // world ptr constructor
				
	virtual // destructor
		~Tracer(void);									

	// functions

	virtual RGBColor
		trace_ray(const Ray& ray) const;

	virtual RGBColor
		trace_ray(const Ray& ray, const int& depth) const;

	virtual RGBColor
		trace_ray(const Ray& ray, double& tmin, const int& depth) const;

protected:
	
	World* world_ptr;
};
