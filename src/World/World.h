#pragma once


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <vector>

#include "ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../Tracers/Tracer.h"
#include "../GeometricObjects/GeometricObject.h"
#include "../GeometricObjects/Sphere.h"
#include "../Utilities/Ray.h"
#include "../Cameras/Camera.h"
#include "../Lights/Light.h"

using namespace std;

class Thread; 	//Connection to Raymond.h


class World {	
public:
	
	ViewPlane						vp;
	RGBColor						background_color;
	Camera*							camera_ptr;
	Tracer*							tracer_ptr;
	std::vector<GeometricObject*>	objects;

	Light*							ambient_ptr;
	std::vector<Light*>				lights;

	int max_samples, sample_batch_size;
	double variance_tolerance;
	
	World(void);
		
	~World();
								
	void 
		add_object(GeometricObject* object_ptr);

	void
		set_ambient_light(Light* amb_ptr);

	void
		add_light(Light* light_ptr);

	void
		set_camera(Camera* c_ptr);
		
	void 					
		build(void);

	//ShadeRec hit_bare_bones_objects(const Ray& ray);

	ShadeRec
		hit_objects(const Ray& raymond) const;
						
private:
		
	void 
		delete_objects(void);

};


// ------------------------------------------------------------------ add_object

inline void 
World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}

inline void
World::set_ambient_light(Light* amb_ptr) {
	ambient_ptr = amb_ptr;
}

inline void
World::add_light(Light* light_ptr) {
	lights.push_back(light_ptr);
}

inline void
World::set_camera(Camera* c_ptr) {
	camera_ptr = c_ptr;
}
