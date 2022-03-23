// this file contains the definition of the World class

#include "../raymond.h"

#include "World.h"
#include "Utilities/Constants.h"

// geometric objects

#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Disk.h"
#include "GeometricObjects/RectangleObject.h"
#include "GeometricObjects/Triangle.h"
#include "GeometricObjects/Torus.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Cylinder.h"

// tracers

#include "Tracers/SingleSphere.h"
#include "Tracers/RayCast.h"
#include "Tracers/AreaLighting.h"
#include "Tracers/Whitted.h"
#include "Tracers/PathTrace.h"
#include "Tracers/GlobalTrace.h"

// utilities

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Point2D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeRec.h"
#include "../Utilities/Maths.h"

// samplers

#include "../Samplers/Sampler.h"
#include "../Samplers/Regular.h"
#include "../Samplers/Random.h"
#include "../Samplers/Jittered.h"
#include "../Samplers/NRooks.h"
#include "../Samplers/MultiJittered.h"
#include "../Samplers/Hammersley.h"

// cameras

#include "../Cameras/Camera.h"
#include "../Cameras/Pinhole.h"
#include "../Cameras/Orthographic.h"

//lights

#include "../Lights/Light.h"
#include "../Lights/Ambient.h"
#include "../Lights/AmbientOccluder.h"
#include "../Lights/PointLight.h"
#include "../Lights/Directional.h"
#include "../Lights/AreaLight.h"
#include "../Lights/EnvironmentLight.h"

// materials

#include "../Materials/Material.h"
#include "../Materials/Matte.h"
#include "../Materials/Phong.h"
#include "../Materials/Emissive.h"
#include "../Materials/Reflective.h"
#include "../Materials/GlossyReflector.h"

// build functions

//#include "../builds/BuildSingleSphere.cpp"
//#include "../builds/BuildMultipleObjects.cpp"
//#include "../builds/BuildBBCoverPic.cpp"
//#include "../builds/BuildSingleSphereSamplerTests.cpp"
//#include "../builds/2SphereShadeTest.cpp"
//#include "../builds/SpecularTest.cpp"
//#include "../builds/ColoredShadows.cpp"
//#include "../builds/AmbientOcclusionTest.cpp"
//#include "../builds/BoxTest.cpp"
//#include "../builds/DiskTest.cpp"
//#include "../builds/RectTest.cpp"
//#include "../builds/TriTest.cpp"
//#include "../builds/TorusTest.cpp"
//#include "../builds/LoopBuildTest.cpp"
//#include "../builds/AreaLightTest.cpp"
//#include "../builds/InstancingTest.cpp"
//#include "../builds/ReflectionTest.cpp"
//#include "../builds/FractalTest.cpp"
//#include "../builds/TorusReflections.cpp"
//#include "../builds/TorusRings.cpp"
//#include "../builds/TorusRings2.cpp"
//#include "../builds/GlossTest.cpp"
//#include "../builds/PurePathTrace.cpp"
//#include "../builds/GlobalTraceTest.cpp"
//#include "../builds/EnvironmentLightTest.cpp"
//#include "../builds/Phong2Test.cpp"
//#include "../builds/OldAllMaterialsTest.cpp"
//#include "../builds/AllMaterialsTest.cpp"
//#include "../builds/CylinderTest.cpp"
//#include "../builds/PhongParamTest.cpp"
#include "../builds/ReflectiveParamTest.cpp"


//#include "../builds/PerformanceTest.cpp"


// -------------------------------------------------------------------- default constructor

World::World(void)
	: background_color(black),
	tracer_ptr(nullptr),
	camera_ptr(nullptr),
	ambient_ptr(nullptr)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = nullptr;
	}	
	
	delete_objects();	
}


// ----------------------------------------------------------------------------- hit_bare_bones_objects

/*
ShadeRec									
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t; 			
	double		tmin 			= kHugeValue;
	int 		num_objects 	= objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t; 
			sr.color			= objects[j]->get_color(); 
		}
		
	return (sr);   
}
*/
ShadeRec
World::hit_objects(const Ray& raymond) const {
	
	ShadeRec sr(*this);
	double t; 
	Normal normal;
	Point3D local_hit_point;
	double tmin = kHugeValue;
	int num_objects = objects.size();

	for (int i = 0; i < num_objects; i++) {
		
		if (objects[i]->hit(raymond, t, sr) && (t < tmin)) {
		
			sr.hit_an_object = true;
			tmin = t;
			sr.material_ptr = objects[i]->get_material();
			sr.hit_point = raymond.o + t * raymond.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}

	if (sr.hit_an_object) {
		
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return sr;
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}


