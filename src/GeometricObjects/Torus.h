#pragma once

#include "GeometricObject.h"
#include "../Utilities/BBox.h"
#include "../Samplers/Sampler.h"

class Torus : public GeometricObject {

public:

	// default constructor
	Torus();

	// component constructor
	Torus(const double _a, const double _b);

	// copy constructor
	Torus(const Torus& rhs);

	// clone
	Torus* clone() const;

	// assignment operator
	Torus& operator=(const Torus& rhs);

	// destructor
	~Torus();

	// returns normal at hitpoint
	Normal compute_normal(const Point3D& p) const;

	// intersect ray with torus
	bool hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	// intersect shadow ray with torus
	bool shadow_hit(const Ray& raymond, double& t) const;

	void set_sampler(Sampler* sampler);

	Point3D sample();

	double pdf(ShadeRec& sr);

	Normal get_normal(const Point3D& p);

private:

	// swept radius
	double a; 

	// tube radius
	double b; 

	// bounding box
	BBox box; 

	Sampler* sampler_ptr;
	double inv_area;
};

inline void
Torus::set_sampler(Sampler* sampler) 
{
	sampler->map_samples_to_torus(a, b);
	sampler_ptr = sampler;
}

inline double
Torus::pdf(ShadeRec& sr) 
{
	return inv_area;
}

inline Normal
Torus::get_normal(const Point3D& p) 
{
	return compute_normal(p);
}

inline Point3D
Torus::sample() 
{
	return sampler_ptr->sample_torus();
}
