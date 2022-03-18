#include "Jittered.h"

Jittered::Jittered()
	: Sampler()
{}

Jittered::Jittered(const int num_samples)
	: Sampler(num_samples) 
{
	generate_samples();
}

Jittered::Jittered(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) 
{
	generate_samples();
}

Jittered::Jittered(const Jittered& rhs)
	: Sampler(rhs) 
{
	generate_samples();
}

Jittered&
Jittered::operator=(const Jittered& rhs) 
{
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

Jittered*
Jittered::clone() const 
{
	return new Jittered(*this);
}

void 
Jittered::generate_samples() 
{
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