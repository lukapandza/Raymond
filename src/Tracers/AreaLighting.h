#pragma once

#include "Tracer.h"

class AreaLighting : public Tracer {
public:

	AreaLighting(void); // default constructor

	AreaLighting(World* _worldPtr); // world ptr constructor

	virtual // destructor
		~AreaLighting(void);

	virtual RGBColor
		trace_ray(const Ray& raymond, const int& depth) const;
};