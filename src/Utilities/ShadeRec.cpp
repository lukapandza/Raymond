// this file contains the definition of the class ShadeRec

// there is no default constructor as the World reference always has to be initialised
// there is also no assignment operator as we don't want to assign the world
// the copy constructor only copies the world reference
// the ray tracer is written so that new ShadeRec objects are always constructed
// using the first constructor or the copy constructor

#include "Constants.h"
#include "ShadeRec.h"
#include "../World/World.h"

// ------------------------------------------------------------------ constructor

ShadeRec::ShadeRec(const World& wr)
	: hit_an_object(false),
	material_ptr(),
	hit_point(),
	local_hit_point(),
	normal(),
	color(black),
	ray(),
	depth(0),
	dir(),
	w(wr)
{}


// ------------------------------------------------------------------ copy constructor

ShadeRec::ShadeRec(const ShadeRec& sr)
	: hit_an_object(sr.hit_an_object),
	material_ptr(sr.material_ptr),
	hit_point(sr.hit_point),
	local_hit_point(sr.local_hit_point),
	normal(sr.normal),
	color(sr.color),
	ray(sr.ray),
	depth(sr.depth),
	dir(sr.dir),
	w(sr.w)
{}
