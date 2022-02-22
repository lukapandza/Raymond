#pragma once

#include "../Samplers/Sampler.h"

class Jittered : public Sampler {
public:
	
	Jittered(void);

	Jittered(const int num_samples);

	Jittered(const int num_samples, const int num_sets);

	Jittered(const Jittered& in);

	Jittered&
	operator= (const Jittered& rhs);

	virtual Jittered*
	clone(void) const;

	virtual
	~Jittered(void);

private:

	virtual void
	generate_samples(void);
};