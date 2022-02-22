#pragma once

#include "../Utilities/RGBColor.h"
class ShadeRec;

class Material {

public:

	Material(void); // defualt constructor

	Material(const Material& rhs); // copy constructor

	virtual Material*
		clone(void) const = 0;

	virtual
		~Material(); // destructor

	Material& // assignment operator
		operator= (const Material& rhs);

	// functions:

	virtual RGBColor
		shade(ShadeRec& sr);

	virtual RGBColor
		area_light_shade(ShadeRec& sr);

	virtual RGBColor
		path_shade(ShadeRec& sr);

	virtual RGBColor
		global_shade(ShadeRec& sr);

	virtual RGBColor
		get_Le(ShadeRec& sr) const;

};