#include "Random.h"

//default constructor:
Random::Random(void)
	: Sampler()
{}

//constructor 1:
Random::Random(const int num_samples)
	: Sampler(num_samples) {
	generate_samples();
}

//constructor 2:
Random::Random(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) {
	generate_samples();
}

//copy constructor:
Random::Random(const Random& rhs)
	: Sampler(rhs) {
	generate_samples();
}

//assignment operator:
Random&
Random::operator=(const Random& rhs) {
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

//clone:
Random*
Random::clone(void) const {
	return (new Random(*this));
}

//destructor:
Random::~Random(void) {}

//generate_samples implementation:

void 
Random::generate_samples(void) {

	// set rand seed:
	set_rand_seed(num_samples);

	for (int set_num = 0; set_num < num_sets; set_num++) {
		for (int sample = 0; sample < num_samples; sample++) {
			samples.push_back(Point2D(rand_float(), rand_float()));
		}
	}
}