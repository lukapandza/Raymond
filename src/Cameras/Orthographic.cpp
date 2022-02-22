/*
#include "Orthographic.h"

// default constructor:
Orthographic::Orthographic(void)
	: Camera()
{}

// copy constructor:
Orthographic::Orthographic(const Orthographic& rhs)
	: Camera()
{}

// clone:
Orthographic*
Orthographic::clone(void) const {
	return new Orthographic(*this);
}

// destructor:
Orthographic::~Orthographic() {}

// assignment operator:
Orthographic&
Orthographic::operator=(const Orthographic& rhs) {
	
	if (this == &rhs)
		return *this;

	Camera::operator=(rhs);

	return *this;
}

void
Orthographic::render_scene(const World& world) {
	
	RGBColor color;
	ViewPlane vp(world.vp);
	Ray raymond;

	int recursion_depth = 0;
	Point2D sp; // sample point in [0, 1]^2
	Point2D pp; // sample point on a pixel

	raymond.d = lookat - eye;
	raymond.d.normalize();

	for (int i = 0; i < vp.vres; i++) {
		for (int ii = 0; i < vp.hres; ii++) {
			
			color = black;

			for (int iii = 0; iii < vp.num_samples; iii++) {
				
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (ii - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (i - 0.5 * vp.vres + sp.y);
				
				Point3D origin = eye + pp.x * u + pp.y * v; //check this.
				raymond.o = origin;

				color += world.tracer_ptr->trace_ray(raymond, recursion_depth);
			}

			color /= vp.num_samples;
			world.display_pixel(i, ii, color);
		}
	}
}
*/