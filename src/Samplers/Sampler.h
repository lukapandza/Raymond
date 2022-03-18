#pragma once

#include <vector>
#include <math.h>

#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Maths.h"

class Sampler {

public:

	// default constructor
	Sampler();

	// samples constructor
	Sampler(const int num);

	// samples, sets constructor
	Sampler(const int num, const int num_sets);

	// copy constructor
	Sampler(const Sampler& s);

	// assignment operator
	Sampler& operator= (const Sampler& rhs);

	// clone
	virtual Sampler* clone() const = 0;

	// set the number of sample sets
	void set_num_sets(const int np);

	// get the number of samples
	int get_num_samples();

	// generate sample patterns in a unit square
	virtual void generate_samples() = 0;

	// set up the randomly shuffled indices
	void setup_shuffled_indices(); 

	// get next sample on unit square
	Point2D sample_unit_square();

	// get next sample on unit disc
	Point2D sample_unit_disk();

	// get next sample on unit hemisphere
	Point3D sample_hemisphere();

	// get next sample on (a, b) torus
	Point3D sample_torus();

	// get next sample on unit sphere
	Point3D sample_unit_sphere();

	void map_samples_to_unit_disk();

	void map_samples_to_hemisphere(const double e);

	void map_samples_to_torus(double a, double b);

	void map_samples_to_unit_sphere();

protected:

	int num_samples;
	int num_sets;
	std::vector<Point2D> samples;
	std::vector<Point2D> disk_samples;
	std::vector<Point3D> hemisphere_samples;
	std::vector<Point3D> torus_samples;
	std::vector<Point3D> sphere_samples;
	std::vector<int> shuffled_indices;
	unsigned long count;
	int jump;
};

inline Point2D
Sampler::sample_unit_square()
{
	if (count % num_samples == 0) // start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;
	return samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

inline Point2D
Sampler::sample_unit_disk()
{
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return disk_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

inline Point3D
Sampler::sample_hemisphere()
{
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

inline Point3D
Sampler::sample_torus()
{
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return torus_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}

inline Point3D
Sampler::sample_unit_sphere()
{
	if (count % num_samples == 0)
		jump = (rand_int() % num_sets) * num_samples;
	return sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]];
}
