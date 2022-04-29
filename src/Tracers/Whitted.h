#pragma once

#include "Tracer.h"

class Whitted : public Tracer {
public:

	Whitted(void); // default constructor

	Whitted(World* _worldPtr); // world ptr constructor

	virtual // destructor
		~Whitted(void);

	virtual RGBColor
		trace_ray(const Ray& raymond, const int& depth) const;

	RGBColor
		trace_ray(const Ray& ray, double& tmin, const int& depth) const;
};