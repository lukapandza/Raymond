#include "Jittered.h"

//default constructor:
Jittered::Jittered(void)
	: Sampler()
{}

//constructor 1:
Jittered::Jittered(const int num_samples)
	: Sampler(num_samples) {
	generate_samples();
}

//constructor 2:
Jittered::Jittered(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) {
	generate_samples();
}

//copy constructor:
Jittered::Jittered(const Jittered& rhs)
	: Sampler(rhs) {
	generate_samples();
}

//assignment operator:
Jittered&
Jittered::operator=(const Jittered& rhs) {
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

//clone:
Jittered*
Jittered::clone(void) const {
	return (new Jittered(*this));
}

//destructor:
Jittered::~Jittered(void) {}

//generate_samples implementation:

void 
Jittered::generate_samples(void) {

	// set rand seed:
	set_rand_seed(num_samples);

	//forcing num_samples into the closest perfect square (side n):
	int n = (int)sqrt((float)num_samples);

	for (int set_num = 0; set_num < num_sets; set_num++) {
		for (int i = 0; i < n; i++) {
			for (int ii = 0; ii < n; ii++) {
				Point2D sp((ii + rand_float()) / n, (i + rand_float()) / n);
				samples.push_back(sp);
			}
		}
	}
}