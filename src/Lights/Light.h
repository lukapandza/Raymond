#pragma once

#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeRec.h"

class Light {

public:

	Light(void); // defualt constructor

	Light(const Light& rhs); // copy constructor

	virtual Light*
		clone(void) const = 0;

	virtual
		~Light(); // destructor

	Light& // assignment operator
		operator= (const Light& rhs);

	virtual Vector3D
		get_direction(ShadeRec& sr) = 0;
	
	virtual RGBColor
		L(ShadeRec& sr) = 0;

	virtual bool
		casts_shadows(void);

	virtual void
		set_shadows(const bool _shadows);

	virtual bool
		in_shadow(const Ray& ray, const ShadeRec& sr) const;

	virtual double 
		G(const ShadeRec& sr) const;

	virtual double 
		pdf(const ShadeRec& sr) const;

protected:

	bool shadows;

};

inline bool
Light::casts_shadows(void) {
	return shadows;
}

inline bool
Light::in_shadow(const Ray& ray, const ShadeRec& sr) const {
	return false;
}

inline double  
Light::G(const ShadeRec& sr) const {
	return 1.0;
}

inline double 
Light::pdf(const ShadeRec& sr) const {
	return 1.0;
}

inline void
Light::set_shadows(const bool _shadows) {
	shadows = _shadows;
}