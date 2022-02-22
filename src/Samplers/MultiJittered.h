#pragma once

#include "../Samplers/Sampler.h"

class MultiJittered : public Sampler {
public:

	MultiJittered(void);

	MultiJittered(const int num_samples);

	MultiJittered(const int num_samples, const int num_sets);

	MultiJittered(const MultiJittered& in);

	MultiJittered&
		operator= (const MultiJittered& rhs);

	virtual MultiJittered*
		clone(void) const;

	virtual
		~MultiJittered(void);

private:

	virtual void
		generate_samples(void);

	void
		shuffle_x_coordinates(int& n);

	void 
		shuffle_y_coordinates(int& n);
};