#pragma once

#include "Tracer.h"

class GlobalTrace : public Tracer {
public:

	GlobalTrace(void); // default constructor

	GlobalTrace(World* _worldPtr); // world ptr constructor

	virtual // destructor
		~GlobalTrace(void);

	virtual RGBColor
		trace_ray(const Ray& raymond, const int& depth) const;
};