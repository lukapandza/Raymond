#pragma once

#include "GeometricObject.h"
#include <vector>

class Compound : public GeometricObject {

public:

	// default constructor
	Compound();

	// copy constructor
	Compound(const Compound& rhs);

	// clone
	Compound* clone() const;

	// assignment operator
	Compound& operator= (const Compound& rhs);

	void set_material(Material* material);

	void add_object(GeometricObject* object);

	bool hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	bool shadow_hit(const Ray& raymond, double& tmin) const;

private:

	std::vector<GeometricObject*> objects;
};