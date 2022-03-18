#pragma once

#include "../Samplers/Sampler.h"

class NRooks : public Sampler {
public:

	// default constructor
	NRooks();

	// samples constructor
	NRooks(const int num_samples);

	// samples, sets constructor
	NRooks(const int num_samples, const int num_sets);

	// copy constructor
	NRooks(const NRooks& in);

	// assignment operator
	NRooks& operator= (const NRooks& rhs);

	// clone
	NRooks* clone() const;

private:

	void generate_samples();

	void shuffle_x_coordinates();

	void shuffle_y_coordinates();
};