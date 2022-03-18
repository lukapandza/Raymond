#include "Random.h"

Random::Random()
	: Sampler()
{}

Random::Random(const int num_samples)
	: Sampler(num_samples) 
{
	generate_samples();
}

Random::Random(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) 
{
	generate_samples();
}

Random::Random(const Random& rhs)
	: Sampler(rhs) 
{
	generate_samples();
}

Random&
Random::operator=(const Random& rhs) 
{
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

Random*
Random::clone() const 
{
	return new Random(*this);
}

void 
Random::generate_samples() {

	// set rand seed:
	set_rand_seed(num_samples);

	for (int set_num = 0; set_num < num_sets; set_num++) 
		for (int sample = 0; sample < num_samples; sample++) 
			samples.push_back(Point2D(rand_float(), rand_float()));
}