#pragma once

#include "GeometricObject.h"

class Disk : public GeometricObject {

public:

	// default constructor
	Disk(); 

	// component constructor
	Disk(const double c_x, const double c_y, const double c_z, const double r, const double n_x, const double n_y, const double n_z);

	// copy constructor
	Disk(const Disk& rhs); 

	// clone
	Disk* clone() const;

	// assignment operator
	Disk& operator=(const Disk& rhs);

	// intersect a ray with the disk
	bool hit(const Ray& raymond, double& t, ShadeRec& s) const;

	// intersect a shadow ray with the disk
	bool shadow_hit(const Ray& raymond, double& t) const;

private:

	// components:
	Point3D center;
	double radius;
	Normal normal;
	double r_squared;
};