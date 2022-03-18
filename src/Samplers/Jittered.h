#pragma once

#include "../Samplers/Sampler.h"

class Jittered : public Sampler {
public:
	
	// default constructor
	Jittered();

	// samples constructor
	Jittered(const int num_samples);

	// samples, sets constructor
	Jittered(const int num_samples, const int num_sets);

	// copy constructor
	Jittered(const Jittered& in);

	// assignment operator
	Jittered& operator= (const Jittered& rhs);

	// clone
	Jittered* clone() const;

private:

	void generate_samples();
};