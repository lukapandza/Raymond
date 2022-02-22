#include "Regular.h"

//default constructor:
Regular::Regular(void)
	: Sampler()
{}

//constructor 1:
Regular::Regular(const int num_samples)
	: Sampler(num_samples) {
	generate_samples();
}

//constructor 2:
Regular::Regular(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) {
	generate_samples();
}

//copy constructor:
Regular::Regular(const Regular& rhs)
	: Sampler(rhs) {
	generate_samples();
}

//assignment operator:
Regular&
Regular::operator=(const Regular& rhs) {
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

//clone:
Regular*
Regular::clone(void) const {
	return (new Regular(*this));
}

//destructor:
Regular::~Regular(void) {}

//generate_samples implementation:

void 
Regular::generate_samples(void) {
	int num = (int)sqrt((float)num_samples);

	for (int set_num = 0; set_num < num_sets; set_num++) {
		for (int i = 0; i < num; i++) {
			for (int ii = 0; ii < num; ii++) {
				samples.push_back(Point2D((ii + 0.5) / num, (i + 0.5) / num));
			}
		}
	}
}