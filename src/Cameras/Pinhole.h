#pragma once

#include "../Utilities/Point2D.h"
#include "../Utilities/Vector3D.h"
#include "../World/World.h"
#include "Camera.h"

class Pinhole: public Camera {

public:

	Pinhole(); // default constructor

	Pinhole(const Pinhole& rhs); // copy constructor

	virtual Pinhole*
		clone(void) const;

	virtual // destructor
		~Pinhole();

	Pinhole& // assignment operator
		operator= (const Pinhole& rhs);

	// setters:

	void
		set_view_distance(const double d);

	void 
		set_zoom(const double zoom);

	// functions:

	Vector3D
		ray_direction(const Point2D& p) const;

	virtual void
		render_scene(const World& world);

	virtual void
		render_scene(const World& world, std::vector<pix_coord>& batch, Thread*& paintArea);

private:

	double d; // view plane to eye distance
	double zoom;
};

// inlined functions:

inline void
Pinhole::set_view_distance(const double distance) {
	d = distance;
}

inline void
Pinhole::set_zoom(const double z) {
	zoom = z;
}
