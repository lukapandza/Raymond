#pragma once

#include "../Samplers/Sampler.h"

class Hammersley : public Sampler {
public:

	// default constructor
	Hammersley();

	// samples constructor
	Hammersley(const int num_samples);

	// samples, sets constructor
	Hammersley(const int num_samples, const int num_sets);

	// copy constructor
	Hammersley(const Hammersley& in);

	// assignment operator
	Hammersley& operator= (const Hammersley& rhs);

	// clone
	virtual Hammersley* clone() const;

private:

	virtual void generate_samples(void);

	double phi(int j);
};