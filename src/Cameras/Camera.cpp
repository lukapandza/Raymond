# include "Camera.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "../raymond.h"
#include "World/World.h"

// default constructor:
Camera::Camera(void)
	: eye(0, 0, 500),
	lookat(0, 0, 0),
	up(0, 1, 0),
	u(1, 0, 0),
	v(0, 1, 0),
	w(0, 0, 1),
	exposure_time(1.0),
	roll_angle(0.0)
{}

// copy constructor:
Camera::Camera(const Camera& rhs)
	: eye(rhs.eye),
	lookat(rhs.lookat),
	up(rhs.up),
	u(rhs.u),
	v(rhs.v),
	w(rhs.w),
	exposure_time(rhs.exposure_time),
	roll_angle(rhs.roll_angle)
{}

// destructor:
Camera::~Camera() {}

//assignment operator:
Camera&
Camera::operator= (const Camera& rhs) {

	if (this == &rhs)
		return *this;

	eye = rhs.eye;
	lookat = rhs.lookat;
	up = rhs.up;
	u = rhs.u;
	v = rhs.v;
	w = rhs.w;
	exposure_time = rhs.exposure_time;
	roll_angle = rhs.roll_angle;

	return *this;
}

void
Camera::compute_uvw(void) {
	
	if (eye.x == lookat.x && eye.z == lookat.z) { // check for singularity cases
		if (eye.y >= lookat.y) { // camera looking down parallel to y
			
			u = Vector3D(0, 0, 1);
			v = Vector3D(1, 0, 0);
			w = Vector3D(0, 1, 0);
		}
		else { //camera looking up parallel to y
			
			u = Vector3D(1, 0, 0);
			v = Vector3D(0, 0, 1);
			w = Vector3D(0, -1, 0);
		}
	}
	else {

		w = eye - lookat;
		w.normalize();

		u = up ^ w;
		u.normalize();

		v = w ^ u;
		v.normalize();
	}
}

pix_coord*
Camera::order_pixels(const int& chunk_size, const int& width, const int& height) {
	
	pix_coord* indices = new pix_coord[width * height];

	struct chunk {
		int ul_x, ul_y, lr_x, lr_y;
	};

	int hor_num_chunks = width / chunk_size;
	if (width % chunk_size > 0)
		hor_num_chunks++;

	int ver_num_chunks = height / chunk_size;
	if (height % chunk_size > 0)
		ver_num_chunks++;

	int num_chunks = hor_num_chunks * ver_num_chunks;

	chunk* chunk_arr = new chunk[num_chunks];

	for (int ch = 0; ch < num_chunks; ch++) {
		
		chunk_arr[ch].ul_x = (ch % hor_num_chunks) * chunk_size;

		chunk_arr[ch].ul_y = ch / hor_num_chunks * chunk_size;

		if ((chunk_arr[ch].ul_x + chunk_size) > width)
			chunk_arr[ch].lr_x = width - 1;
		else
			chunk_arr[ch].lr_x = chunk_arr[ch].ul_x + chunk_size - 1;

		if ((chunk_arr[ch].ul_y + chunk_size) > height)
			chunk_arr[ch].lr_y = height - 1;
		else
			chunk_arr[ch].lr_y = chunk_arr[ch].ul_y + chunk_size - 1;
	}

	//shuffle chunks:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(chunk_arr, chunk_arr + num_chunks, std::default_random_engine(seed));

	int curr_index = 0;

	for (int ch = 0; ch < num_chunks; ch++) {

		int hor_chunk_size = chunk_arr[ch].lr_x - chunk_arr[ch].ul_x + 1;
		int ver_chunk_size = chunk_arr[ch].lr_y - chunk_arr[ch].ul_y + 1;
		int num_pixels = hor_chunk_size * ver_chunk_size;

		pix_coord* chunk_pixels = new pix_coord[num_pixels];
		for (int i = 0; i < num_pixels; i++) {
			chunk_pixels[i].x = chunk_arr[ch].ul_x + (i % hor_chunk_size);
			chunk_pixels[i].y = chunk_arr[ch].ul_y + (i / hor_chunk_size);
		}

		seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(chunk_pixels, chunk_pixels + num_pixels, std::default_random_engine(seed));

		for (int i = 0; i < num_pixels; i++) {
			indices[curr_index + i] = chunk_pixels[i];
		}
		curr_index += num_pixels;
	}

	return indices;
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
Camera::display_pixel(const int row, const int column, const RGBColor& raw_color, const World& w, Thread*& paintArea) const {

	RGBColor mapped_color;

	if (w.vp.show_out_of_gamut)
		mapped_color = raw_color.clamp_to_red();
	else
		mapped_color = raw_color.max_to_one();

	if (w.vp.gamma != 1.0)
		mapped_color = mapped_color.powc(w.vp.inv_gamma);

	//have to start from max y coordinate to convert to screen coordinates
	int x = column;
	int y = w.vp.vres - row - 1;

	paintArea->SetPixel(x, y, 
		(int)(mapped_color.r * 255),
		(int)(mapped_color.g * 255),
		(int)(mapped_color.b * 255));
}