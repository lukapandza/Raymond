#pragma once

#include "GeometricObject.h"

class Cylinder : public GeometricObject {

public:

	// default constructor
	Cylinder();

	// component constructor
	Cylinder(const double y_0, const double y_1, const double r);

	// copy constructor
	Cylinder(const Cylinder& rhs);

	// clone
	Cylinder* clone() const;

	// assignment operator
	Cylinder& operator=(const Cylinder& rhs);

	// intersect ray with cylinder
	bool hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	// intersect shadow ray with cylinder
	bool shadow_hit(const Ray& raymond, double& tmin) const;

private:

	// end
	double y_0, y_1;

	//radius
	double r;
};