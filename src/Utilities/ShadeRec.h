#pragma once

class World;	// forward declaration
#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"
#include "../Materials/Material.h"

class ShadeRec {
public:
	
	// did the ray hit an object?
	bool hit_an_object;

	// material of hit object
	Material* material_ptr;

	// world coordinates of hit point
	Point3D	hit_point;

	// local coordinates of hit point 
	Point3D	local_hit_point;

	// normal at hit point
	Normal normal;

	// used in Chapter 3 only
	RGBColor color;

	// for specular highlights
	Ray ray;

	// recursion depth
	int depth;

	// for area lights
	Vector3D dir;

	// world reference for shading
	const World& w;

	double t;
	
	// world constructor
	ShadeRec(const World& wr);

	// copy constructor
	ShadeRec(const ShadeRec& sr);
};
