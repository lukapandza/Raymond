#pragma once

#include "../Samplers/Sampler.h"

class Regular : public Sampler {
public:

	Regular(void);

	Regular(const int num_samples);

	Regular(const int num_samples, const int num_sets);

	Regular(const Regular& in);

	Regular&
		operator= (const Regular& rhs);

	virtual Regular*
		clone(void) const;

	virtual
		~Regular(void);

private:

	virtual void
		generate_samples(void);
};