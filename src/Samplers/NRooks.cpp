#include "NRooks.h"

//default constructor:
NRooks::NRooks(void)
	: Sampler()
{}

//constructor 1:
NRooks::NRooks(const int num_samples)
	: Sampler(num_samples) {
	generate_samples();
}

//constructor 2:
NRooks::NRooks(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) {
	generate_samples();
}

//copy constructor:
NRooks::NRooks(const NRooks& rhs)
	: Sampler(rhs) {
	generate_samples();
}

//assignment operator:
NRooks&
NRooks::operator=(const NRooks& rhs) {
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

//clone:
NRooks*
NRooks::clone(void) const {
	return (new NRooks(*this));
}

//destructor:
NRooks::~NRooks(void) {}

//generate_samples implementation:

void 
NRooks::generate_samples(void) {

	// set rand seed:
	set_rand_seed(num_samples);

	//generate samples along the main (y=x) diagonal:
	for (int i = 0; i < num_sets; i++) {
		for (int ii = 0; ii < num_samples; ii++) {
			double x_coord = (ii + rand_float()) / num_samples;
			double y_coord = (ii + rand_float()) / num_samples;
			samples.push_back(Point2D(x_coord, y_coord));
		}
	}

	//break up the diagonal:
	shuffle_x_coordinates();
	shuffle_y_coordinates();
}

void
NRooks::shuffle_x_coordinates(void) {
	for (int i = 0; i < num_sets; i++) {
		for (int ii = 0; ii < num_samples - 1; ii++) {
			int target = rand_int() % num_samples + i * num_samples;
			double temp = samples[ii + i * num_samples + 1].x;
			samples[ii + i * num_samples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
	}
}

void
NRooks::shuffle_y_coordinates(void) {
	for (int i = 0; i < num_sets; i++) {
		for (int ii = 0; ii < num_samples - 1; ii++) {
			int target = rand_int() % num_samples + i * num_samples;
			double temp = samples[ii + i * num_samples + 1].y;
			samples[ii + i * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}