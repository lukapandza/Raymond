#include "Constants.h"
#include "ShadeRec.h"
#include "../World/World.h"

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
