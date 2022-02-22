#pragma once

#include "../Samplers/Sampler.h"

class NRooks : public Sampler {
public:

	NRooks(void);

	NRooks(const int num_samples);

	NRooks(const int num_samples, const int num_sets);

	NRooks(const NRooks& in);

	NRooks&
		operator= (const NRooks& rhs);

	virtual NRooks*
		clone(void) const;

	virtual
		~NRooks(void);

private:

	virtual void
		generate_samples(void);

	void
		shuffle_x_coordinates(void);

	void
		shuffle_y_coordinates(void);
};