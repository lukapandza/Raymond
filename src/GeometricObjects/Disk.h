#pragma once

#include "GeometricObject.h"

class Disk : public GeometricObject {

public:

	Disk(void); // default constructor

	Disk(const double c_x, const double c_y, const double c_z, const double r, const double n_x, const double n_y, const double n_z);

	Disk(const Disk& rhs); // copy constructor

	Disk*
		clone(void) const;

	Disk&
		operator=(const Disk& rhs);

	~Disk(void);

	bool
		hit(const Ray& raymond, double& t, ShadeRec& s) const;

	bool
		shadow_hit(const Ray& raymond, double& t) const;

private:

	Point3D center;
	double radius;
	Normal normal;
	double r_squared;
};