#pragma once

#include "../Samplers/Sampler.h"

class MultiJittered : public Sampler {
public:

	// default constructor
	MultiJittered();

	// samples constructor
	MultiJittered(const int num_samples);

	// samples, sets constructor
	MultiJittered(const int num_samples, const int num_sets);

	// copy constructor
	MultiJittered(const MultiJittered& in);

	// assignment operator
	MultiJittered& operator= (const MultiJittered& rhs);

	// clone
	MultiJittered* clone() const;

private:

	void generate_samples();

	void shuffle_x_coordinates(int& n);

	void shuffle_y_coordinates(int& n);
};