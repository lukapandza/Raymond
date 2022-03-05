#pragma once

#include "Light.h"
#include "../Samplers/Sampler.h"

class EnvironmentLight : public Light {

public:

	EnvironmentLight();

	EnvironmentLight(const EnvironmentLight& rhs);

	EnvironmentLight*
		clone() const;

	~EnvironmentLight();

	EnvironmentLight&
		operator=(const EnvironmentLight& rhs);

	void
		set_sampler(Sampler* sampler);

	void
		set_material(Material* material);

	virtual Vector3D
		get_direction(ShadeRec& sr);

	virtual RGBColor
		L(ShadeRec& sr);

	bool
		in_shadow(const Ray& raymond, const ShadeRec& sr) const;

	virtual double
		pdf(const ShadeRec& sr) const;

private:
	Sampler* sampler_ptr;
	Material* material_ptr;
	Vector3D u, v, w;
	Vector3D wi;
};

inline void
EnvironmentLight::set_material(Material* material) {
	this->material_ptr = material;
}
