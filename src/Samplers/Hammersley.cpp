#include "Hammersley.h"

Hammersley::Hammersley()
	: Sampler()
{}

Hammersley::Hammersley(const int num_samples)
	: Sampler(num_samples) 
{
	generate_samples();
}

Hammersley::Hammersley(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) 
{
	generate_samples();
}

Hammersley::Hammersley(const Hammersley& rhs)
	: Sampler(rhs) 
{
	generate_samples();
}

Hammersley&
Hammersley::operator=(const Hammersley& rhs) 
{
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

Hammersley*
Hammersley::clone(void) const
{
	return new Hammersley(*this);
}

void
Hammersley::generate_samples(void) {
	for (int set = 0; set < num_sets; set++) {
		for (int i = 0; i < num_samples; i++) {
			double x_coord = (float)i / (float)num_samples;
			samples.push_back(Point2D(x_coord, phi(i)));
		}
	}
}

double
Hammersley::phi(int i) {
	double x = 0.0;
	double f = 0.5;

	while (i) {
		x += f * (double)(i % 2);
		i /= 2;
		f *= 0.5;
	}

	return (x);
}