#pragma once

class World;	// forward declaration
#include "Point3D.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Ray.h"
#include "../Materials/Material.h"

class ShadeRec {
public:
	
	//member variables:
	bool				hit_an_object;		// did the ray hit an object?
	Material*			material_ptr;		// nearest object’s material
	Point3D				hit_point;			// world coordinates of hit point
	Point3D				local_hit_point;	// world coordinates of hit point 
	Normal				normal;				// normal at hit point
	RGBColor			color;				// used in Chapter 3 only
	Ray					ray;				// for specular highlights
	int					depth;				// recursion depth
	Vector3D			dir;				// for area lights
	const World&		w;					// world reference for shading
	
	ShadeRec(const World& wr);				// constructor
	ShadeRec(const ShadeRec& sr);			// copy constructor
};
