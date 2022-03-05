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

// tracers

#include "Tracers/SingleSphere.h"
#include "Tracers/MultipleObjects.h"
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
#include "../builds/GlossTest.cpp"
//#include "../builds/PurePathTrace.cpp"
//#include "../builds/GlobalTraceTest.cpp"

//#include "../builds/PerformanceTest.cpp"


// -------------------------------------------------------------------- default constructor

World::World(void)
	: background_color(black),
	tracer_ptr(NULL),
	camera_ptr(NULL),
	ambient_ptr(NULL)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
	if(tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}	
	
	delete_objects();	
}


// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
	double max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}


// ---------------------------------------------------------------------------display_pixel

// raw_color is the pixel color computed by the ray tracer
// its RGB doubleing point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still doubleing point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	
	/*
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);
	
   //have to start from max y coordinate to convert to screen coordinates
   int x = column;
   int y = vp.vres - row - 1;

   paintArea->SetPixel(x, y, (int)(mapped_color.r * 255),
                             (int)(mapped_color.g * 255),
                             (int)(mapped_color.b * 255));
	*/

	RGBColor mapped_color;

	if (this->vp.show_out_of_gamut)
		mapped_color = raw_color.clamp_to_red();
	else
		mapped_color = raw_color.max_to_one();

	if (this->vp.gamma != 1.0)
		mapped_color = mapped_color.powc(this->vp.inv_gamma);


	//have to start from max y coordinate to convert to screen coordinates
	int x = column;
	int y = this->vp.vres - row - 1;

	this->paintArea->SetPixel(x, y,
		(int)(mapped_color.r * 255),
		(int)(mapped_color.g * 255),
		(int)(mapped_color.b * 255));
}



// ----------------------------------------------------------------------------- hit_bare_bones_objects

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

ShadeRec
World::hit_objects(const Ray& raymond) const {
	
	//World wr = *this;
	ShadeRec sr(*this);
	//ShadeRec* sr = new ShadeRec(*this);
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
		
		//sr.t = tmin; no t?
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


