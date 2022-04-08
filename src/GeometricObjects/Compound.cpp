#include "Compound.h"
#include "../Utilities/Constants.h"

Compound::Compound()
	: GeometricObject(),
	objects(std::vector<GeometricObject*>())
{}

Compound::Compound(const Compound& rhs)
	: GeometricObject(rhs),
	objects(std::vector<GeometricObject*>(rhs.objects))
{}

Compound* 
Compound::clone() const
{
	return new Compound(*this);
}

Compound& 
Compound::operator= (const Compound& rhs)
{
	if (this == &rhs)
		return *this;

	GeometricObject::operator= (rhs);
	this->objects = std::vector<GeometricObject*>(rhs.objects);

	return *this;
}

void
Compound::set_material(Material* material)
{
	for (int i(0); i < objects.size(); i++)
		objects[i]->set_material(material);
}

void
Compound::add_object(GeometricObject* object)
{
	this->objects.push_back(object);
}

bool
Compound::hit(const Ray& raymond, double& tmin, ShadeRec& sr) const
{
	double t;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
	int num_objects = this->objects.size();

	for (int i(0); i < num_objects; i++)
		if (this->objects[i]->hit(raymond, t, sr) && (t < tmin)) {
			hit = true;
			tmin = t;
			material_ptr = objects[i]->get_material();
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}

	if (hit) {
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return hit;
}

bool
Compound::shadow_hit(const Ray& raymond, double& tmin) const
{
	double t;
	bool hit = false;
	int num_objects = this->objects.size();

	for (int i(0); i < num_objects; i++)
		if (this->objects[i]->shadow_hit(raymond, t) && t < tmin) {
			hit = true;
			tmin = t;
		}

	return hit;
}
