#pragma once

#include "../Samplers/Sampler.h"

class Regular : public Sampler {
public:

	// default constructor
	Regular();

	// samples constructor
	Regular(const int num_samples);

	// samples, sets constructor
	Regular(const int num_samples, const int num_sets);

	// copy constructor
	Regular(const Regular& in);

	// assignment operator
	Regular& operator= (const Regular& rhs);

	// clone
	Regular* clone() const;

private:

	// sample distribution function
	void generate_samples();
};