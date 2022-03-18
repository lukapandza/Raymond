#include "NRooks.h"

NRooks::NRooks()
	: Sampler()
{}

NRooks::NRooks(const int num_samples)
	: Sampler(num_samples) 
{
	generate_samples();
}

NRooks::NRooks(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) 
{
	generate_samples();
}

NRooks::NRooks(const NRooks& rhs)
	: Sampler(rhs) 
{
	generate_samples();
}

NRooks&
NRooks::operator=(const NRooks& rhs) 
{
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

NRooks*
NRooks::clone() const 
{
	return new NRooks(*this);
}

void 
NRooks::generate_samples() 
{
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
NRooks::shuffle_x_coordinates() 
{
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
NRooks::shuffle_y_coordinates() {
	for (int i = 0; i < num_sets; i++) {
		for (int ii = 0; ii < num_samples - 1; ii++) {
			int target = rand_int() % num_samples + i * num_samples;
			double temp = samples[ii + i * num_samples + 1].y;
			samples[ii + i * num_samples + 1].y = samples[target].y;
			samples[target].y = temp;
		}
	}
}