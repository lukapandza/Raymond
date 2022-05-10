
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
Orthographic::render_scene(const World& world, std::vector<pix_coord>& batch, Thread*& paintArea) {
	
	RGBColor color;
	ViewPlane vp(world.vp);

	int recursion_depth = 0;
	Point2D sp; // sample point in [0, 1]^2
	Point2D pp; // sample point on a pixel

	int num_pixels = batch.size();

	for (int p = 0; p < num_pixels; p++) {

		int i = batch[p].y;
		int ii = batch[p].x;

		color = black;
		for (int iii = 0; iii < vp.num_samples; iii++) {

			sp = vp.sampler_ptr->sample_unit_square();
			pp.x = vp.s * (ii - vp.half_hres + sp.x);
			pp.y = vp.s * (i - vp.half_vres + sp.y);

			Point3D origin = eye + pp.x * u + pp.y * v; //check this.

			color += world.tracer_ptr->trace_ray(Ray(origin, dir), 0);
		}

		color /= vp.num_samples;
		color *= exposure_time;

		display_pixel(i, ii, color, world, paintArea);
	}

	/*
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
	*/
}

RGBColor
Orthographic::sample_pixel(World* w, int h, int v)
{
	Point2D sp(w->vp.sampler_ptr->sample_unit_square());
	Point2D pp(w->vp.s * (h - w->vp.half_hres + sp.x), w->vp.s * (v - w->vp.half_vres + sp.y));

	Point3D origin = eye + pp.x * u + pp.y * this->v; //check this.
	return w->tracer_ptr->trace_ray(Ray(origin, dir), 0);
}

void
Orthographic::compute_dir() 
{
	dir = lookat - eye;
	dir.normalize();
}