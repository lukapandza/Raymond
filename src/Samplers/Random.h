#pragma once

#include "../Samplers/Sampler.h"

class Random : public Sampler {
public:

	// default constructor
	Random();

	// samples constructor
	Random(const int num_samples);

	// samples, sets constructor
	Random(const int num_samples, const int num_sets);

	// copy constructor
	Random(const Random& in);

	// assignment operator
	Random& operator= (const Random& rhs);

	// clone
	virtual Random* clone() const;

private:

	// sample distribution function
	virtual void generate_samples();
};