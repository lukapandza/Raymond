#pragma once

#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"
#include "../raymond.h"

class World; //because World includes Camera.h

class Camera {

public:

	Camera(); //default constructor

	Camera(const Camera& rhs); //copy constructor

	virtual Camera* 
		clone(void) const = 0;

	virtual
		~Camera(); //destructor

	Camera& // assignment operator
		operator= (const Camera& rhs);

	//setters:

	void
		set_eye(const Point3D& p);

	void
		set_eye(const double x, const double y, const double z);

	void
		set_lookat(const Point3D& p);

	void
		set_lookat(const double x, const double y, const double z);

	void
		set_up_vector(const Vector3D& v);

	void
		set_up_vector(const double x, const double y, const double z);

	void
		set_exposure_time(const double t);

	void
		set_roll(const double angle);

	//functions:

	void 
		compute_uvw(void);

	pix_coord*
		order_pixels(const int& chunk_size, const int& width, const int& height);

	virtual void
		render_scene(const World& w, std::vector<pix_coord>& batch, Thread*& paintArea) = 0;

	void
		display_pixel(const int row, const int column, const RGBColor& raw_color, const World& w, Thread*& paintArea) const;

protected:

	Point3D eye;
	Point3D lookat;
	Vector3D up;
	Vector3D u, v, w;
	double exposure_time;
	double roll_angle;
};

//inlined functions:

inline void
Camera::set_eye(const Point3D& p) {
	eye = p;
}

inline void
Camera::set_eye(const double x, const double y, const double z) {
	eye.x = x;
	eye.y = y;
	eye.z = z;
}

inline void
Camera::set_lookat(const Point3D& p) {
	lookat = p;
}

inline void
Camera::set_lookat(const double x, const double y, const double z) {
	lookat.x = x;
	lookat.y = y;
	lookat.z = z;
}

inline void
Camera::set_up_vector(const Vector3D& v) {
	up = v;
}

inline void
Camera::set_up_vector(const double x, const double y, const double z) {
	up.x = x;
	up.y = y;
	up.z = z;
}

inline void
Camera::set_exposure_time(const double t) {
	exposure_time = t;
}

inline void
Camera::set_roll(const double angle) {
	roll_angle = angle;
}
