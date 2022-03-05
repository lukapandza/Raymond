#include "EnvironmentLight.h"
#include "../World/World.h"

EnvironmentLight::EnvironmentLight() 
	: Light(),
	sampler_ptr(nullptr),
	material_ptr(nullptr)
{}

EnvironmentLight::EnvironmentLight(const EnvironmentLight& rhs) 
	: Light(rhs) {
	
	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();
	else  sampler_ptr = nullptr;

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();
	else  material_ptr = nullptr;
}

EnvironmentLight*
EnvironmentLight::clone() const {
	return new EnvironmentLight(*this);
}

EnvironmentLight::~EnvironmentLight() {
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (material_ptr) {
		delete material_ptr;
		material_ptr = nullptr;
	}
}

EnvironmentLight&
EnvironmentLight::operator=(const EnvironmentLight& rhs) {
	
	if (this == &rhs)
		return (*this);

	Light::operator=(rhs);

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	if (rhs.sampler_ptr)
		sampler_ptr = rhs.sampler_ptr->clone();

	if (material_ptr) {
		delete material_ptr;
		material_ptr = nullptr;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return *this;
}

void
EnvironmentLight::set_sampler(Sampler* sampler) {
	
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = nullptr;
	}

	sampler_ptr = sampler;
	sampler_ptr->map_samples_to_hemisphere(1);
}

Vector3D
EnvironmentLight::get_direction(ShadeRec& sr) {
	
	this->w = sr.normal;
	this->v = Vector3D(0.0034, 1, 0.0071) ^ this->w;
	this->v.normalize();
	this->u = this->v ^ this->w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	this->wi = sp.x * u + sp.y * v + sp.z * this->w;
	return this->wi;
}

RGBColor
EnvironmentLight::L(ShadeRec& sr) {
	return this->material_ptr->get_Le(sr);
}

bool
EnvironmentLight::in_shadow(const Ray& raymond, const ShadeRec& sr) const {
	
	double t;
	int num_objects = sr.w.objects.size();

	for (int i = 0; i < num_objects; i++)
		if (sr.w.objects[i]->shadow_hit(raymond, t))
			return true;

	return false;
}

double
EnvironmentLight::pdf(const ShadeRec& sr) const {
	return sr.normal* wi* invPI;
}
