#pragma once

#include "Compound.h"
#include "../Utilities/BBox.h"

class Grid : public Compound 
{
public:

	// default constructor
	Grid();

	// copy constructor
	Grid(const Grid& rhs);

	// clone
	Grid* clone() const;

	Grid& operator= (const Grid& rhs);

	BBox get_bounding_box();

	void setup_cells();

	bool hit(const Ray& raymond, double& tmin, ShadeRec& sr) const;

	bool shadow_hit(const Ray& raymond, double& tmin) const;

private:

	std::vector<GeometricObject*> cells;
	BBox bbox;
	int nx, ny, nz;

	Point3D min_coordinates();

	Point3D max_coordinates();
};

inline BBox Grid::get_bounding_box()
{
	return this->bbox;
}
