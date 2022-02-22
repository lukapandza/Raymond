#pragma once

#include "GeometricObject.h"
#include "../Utilities/BBox.h"
#include "../Samplers/Sampler.h"

class Torus : public GeometricObject {

public:

	Torus(void);

	Torus(const double _a, const double _b);

	Torus(const Torus& rhs);

	Torus*
		clone(void) const;

	Torus&
		operator=(const Torus& rhs);

	~Torus(void);

	Normal
		compute_normal(const Point3D& p) const;

	bool
		hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	bool
		shadow_hit(const Ray& raymond, double& t) const;

	void
		set_sampler(Sampler* sampler);

	Point3D
		sample(void);

	double
		pdf(ShadeRec& sr);

	Normal
		get_normal(const Point3D& p);

private:

	double a; // swept radius
	double b; // tube radius
	BBox box; // bounding box

	Sampler* sampler_ptr;
	double inv_area;
};

inline void
Torus::set_sampler(Sampler* sampler) {
	sampler->map_samples_to_torus(a, b);
	sampler_ptr = sampler;
}

inline double
Torus::pdf(ShadeRec& sr) {
	return inv_area;
}

inline Normal
Torus::get_normal(const Point3D& p) {
	return compute_normal(p);
}

inline Point3D
Torus::sample(void) {
	return sampler_ptr->sample_torus();
}
