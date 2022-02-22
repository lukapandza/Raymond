#pragma once

#include "Tracer.h"

class RayCast : public Tracer {
public:

	RayCast(void); // default constructor

	RayCast(World* _worldPtr); // world ptr constructor

	virtual // destructor
		~RayCast(void);

	virtual RGBColor
		trace_ray(const Ray& raymond, const int& depth) const;
};