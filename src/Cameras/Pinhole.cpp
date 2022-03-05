#include "Pinhole.h"

// default constructor:
Pinhole::Pinhole(void)
	: Camera(),
	d(500),
	zoom(1.0)
{}

// copy constructor
Pinhole::Pinhole(const Pinhole& rhs)
	: Camera(rhs),
	d(rhs.d),
	zoom(rhs.zoom)
{}

// clone:
Pinhole*
Pinhole::clone(void) const {
	return new Pinhole(*this);
}

// desturctor:
Pinhole::~Pinhole() {}

//assignment operator:
Pinhole&
Pinhole::operator=(const Pinhole& rhs) {
	
	if (this == &rhs)
		return *this;

	Camera::operator=(rhs);
	d = rhs.d;
	zoom = rhs.zoom;

	return *this;
}

Vector3D
Pinhole::ray_direction(const Point2D& p) const {
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	return(dir);
}

void
Pinhole::render_scene(const World& world, std::vector<pix_coord>& batch, Thread*& paintArea) {

	RGBColor color;
	ViewPlane vp(world.vp);
	Ray raymond;

	int recursion_depth = 0;
	Point2D sp; // sample point in [0, 1]^2
	Point2D pp; // sample point on a pixel

	vp.s /= zoom;
	raymond.o = eye;

	int num_pixels = batch.size();

	for (int p = 0; p < num_pixels; p++) {

		int i = batch[p].y;
		int ii = batch[p].x;

		color = black;
		for (int iii = 0; iii < vp.num_samples; iii++) {

			sp = vp.sampler_ptr->sample_unit_square();
			pp.x = vp.s * (ii - vp.half_hres + sp.x);
			pp.y = vp.s * (i - vp.half_vres + sp.y);

			raymond.d = ray_direction(pp);

			color += world.tracer_ptr->trace_ray(raymond, recursion_depth);
		}

		color /= vp.num_samples;
		color *= exposure_time;

		display_pixel(i, ii, color, world, paintArea);
	}
}