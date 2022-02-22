#pragma once

#include <vector>
#include <math.h>

#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Maths.h"

class Sampler {

public:

	//constructors:
	Sampler(void);

	Sampler(const int num);

	Sampler(const int num, const int num_sets);

	Sampler(const Sampler& s);

	Sampler&
		operator= (const Sampler& rhs);

	virtual Sampler*
		clone(void) const = 0;

	virtual
		~Sampler(void);

	//getters and setters:
	void
		set_num_sets(const int np);

	int
		get_num_samples(void);

	virtual void //generate sample patterns in a unit square
		generate_samples(void) = 0;

	void
		setup_shuffled_indices(void); //set up the randomly shuffled indices

	Point2D //get next sample on unit square
		sample_unit_square(void);

	Point2D //get next sample on unit disc
		sample_unit_disk(void);

	Point3D //get next sample on unit hemisphere
		sample_hemisphere(void);

	Point3D
		sample_torus(void);

	Point3D
		sample_unit_sphere(void);

	void
		map_samples_to_unit_disk(void);

	void 
		map_samples_to_hemisphere(const double e);

	void
		map_samples_to_torus(double a, double b);

	void
		map_samples_to_unit_sphere(void);

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

