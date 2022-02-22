#pragma once

#include "../Samplers/Sampler.h"

class Hammersley : public Sampler {
public:

	Hammersley(void);

	Hammersley(const int num_samples);

	Hammersley(const int num_samples, const int num_sets);

	Hammersley(const Hammersley& in);

	Hammersley&
		operator= (const Hammersley& rhs);

	virtual Hammersley*
		clone(void) const;

	virtual
		~Hammersley(void);

private:

	virtual void
		generate_samples(void);

	double
		phi(int j);
};