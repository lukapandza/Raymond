#include "MultiJittered.h"

MultiJittered::MultiJittered()
	: Sampler()
{}

MultiJittered::MultiJittered(const int num_samples)
	: Sampler(num_samples) 
{
	generate_samples();
}

MultiJittered::MultiJittered(const int num_samples, const int num_sets)
	: Sampler(num_samples, num_sets) 
{
	generate_samples();
}

MultiJittered::MultiJittered(const MultiJittered& rhs)
	: Sampler(rhs) 
{
	generate_samples();
}

MultiJittered&
MultiJittered::operator=(const MultiJittered& rhs) 
{
	if (this == &rhs)
		return *this;

	Sampler::operator= (rhs);

	return *this;
}

MultiJittered*
MultiJittered::clone() const 
{
	return new MultiJittered(*this);
}

void
MultiJittered::generate_samples() 
{
	// set rand seed:
	set_rand_seed(num_samples);

	//n is side of closest perfect square to num_samples:
	int n = (int)sqrt((float)num_samples);
	double subsquare_side = 1.0 / ((float)num_samples);

	//initialize samples with empty points:
	Point2D def;
	for (int i = 0; i < num_sets * num_samples; i++)
		samples.push_back(def);

	//distribution in the initial pattern (see Figure 5.11b):
	for (int set = 0; set < num_sets; set++) {
		for (int i = 0; i < n; i++) {
			for (int ii = 0; ii < n; ii++) {
				samples[n * i + ii + set * num_samples].x = (n * i + ii) * subsquare_side + rand_float(0, subsquare_side);
				samples[n * i + ii + set * num_samples].y = (n * ii + i) * subsquare_side + rand_float(0, subsquare_side);
			}
		}	
	}

	shuffle_x_coordinates(n);
	shuffle_y_coordinates(n);
}

void
MultiJittered::shuffle_x_coordinates(int& n) 
{
	for (int set = 0; set < num_sets; set++) {
		for (int i = 0; i < n; i++) {
			for (int ii = 0; ii < n; ii++) {
				int j = rand_int(ii, n - 1);
				double temp = samples[n * i + ii + set * num_samples].x;
				samples[n * i + ii + set * num_samples].x = samples[n * i + j + set * num_samples].x;
				samples[n * i + j + set * num_samples].x = temp;
			}
		}
	}
}

void
MultiJittered::shuffle_y_coordinates(int& n) 
{
	for (int set = 0; set < num_sets; set++) {
		for (int i = 0; i < n; i++) {
			for (int ii = 0; ii < n; ii++) {
				int j = rand_int(ii, n - 1);
				double temp = samples[i + n * ii + set * num_samples].y;
				samples[i + n * ii + set * num_samples].y = samples[i + n * ii + set * num_samples].y;
				samples[i + n * ii + set * num_samples].y = temp;
			}
		}
	}
}