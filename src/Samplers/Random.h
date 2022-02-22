#pragma once

#include "../Samplers/Sampler.h"

class Random : public Sampler {
public:

	Random(void);

	Random(const int num_samples);

	Random(const int num_samples, const int num_sets);

	Random(const Random& in);

	Random&
		operator= (const Random& rhs);

	virtual Random*
		clone(void) const;

	virtual
		~Random(void);

private:

	virtual void
		generate_samples(void);
};