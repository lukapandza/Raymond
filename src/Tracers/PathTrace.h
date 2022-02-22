#pragma once

#include "Tracer.h"

class PathTrace : public Tracer {
public:

	PathTrace(void); // default constructor

	PathTrace(World* _worldPtr); // world ptr constructor

	virtual // destructor
		~PathTrace(void);

	virtual RGBColor
		trace_ray(const Ray& raymond, const int& depth) const;
};