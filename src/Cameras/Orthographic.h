/*
#pragma once

#include "../World/World.h"
#include "Camera.h"

class Orthographic : public Camera {

public:
	Orthographic(); // default constructor

	Orthographic(const Orthographic& rhs); //copy constructor

	virtual Orthographic*
		clone(void) const;

	virtual // destructor
		~Orthographic();

	Orthographic& // assignment operator
		operator= (const Orthographic& rhs);

	// functions:

	virtual void
		render_scene(const World& world);
};
*/