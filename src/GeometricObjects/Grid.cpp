#include "Grid.h"
#include "../Utilities/Constants.h"

Grid::Grid()
	: Compound(), 
	cells(std::vector<GeometricObject*>()),
	bbox(BBox()),
	nx(1), ny(1), nz(1)
{}

Grid::Grid(const Grid& rhs)
	: Compound(rhs),
	cells(rhs.cells),
	bbox(rhs.bbox),
	nx(rhs.nx), ny(rhs.ny), nz(rhs.nz)
{}

Grid* 
Grid::clone() const 
{
	return new Grid(*this);
}

Grid& 
Grid::operator= (const Grid& rhs) 
{
	if (this == &rhs)
		return *this;

	Compound::operator=(rhs);

	this->cells = rhs.cells;
	this->bbox = rhs.bbox;
	this->nx = rhs.nx;
	this->ny = rhs.ny;
	this->nz = rhs.nz;

	return *this;
}

void
Grid::setup_cells() 
{
	// min and max points of grid:
	Point3D p0 = min_coordinates();
	Point3D p1 = max_coordinates();

	this->bbox = BBox(p0.x, p0.y, p0.z, p1.x, p1.y, p1.z);

	// compute the number of cells in the x-, y-, and z-directions
	int num_objects = objects.size();
	double wx = p1.x - p0.x; // grid extent in x-direction
	double wy = p1.y - p0.y; // grid extent in y-direction
	double wz = p1.z - p0.z; // grid extent in z-direction
	double multiplier = 2.0; // about 8 times more cells than objects
	double s = pow(wx * wy * wz / num_objects, 0.3333333);

	this->nx = multiplier * wx / s + 1;
	this->ny = multiplier * wy / s + 1;
	this->nz = multiplier * wz / s + 1;

	// set up the array of cells with null pointers
	int num_cells = nx * ny * nz;

	cells.reserve(num_objects);
	for (int i(0); i < num_cells; i++)
		cells.push_back(nullptr);

	// set up a temporary array to hold the number of objects stored in each cell
	std::vector<int> counts;

	counts.reserve(num_cells);
	for (int j = 0; j < num_cells; j++)
		counts.push_back(0);

	// put objects into the cells
	BBox obj_bbox; // object?s bounding box
	int index; // cells array index

	for (int i(0); i < num_objects; i++) {
	
		obj_bbox = objects[i]->get_bounding_box();

		// compute the cell indices for the corners of the bounding box of the object

		int ixmin = clamp((obj_bbox.x0 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymin = clamp((obj_bbox.y0 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmin = clamp((obj_bbox.z0 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
		int ixmax = clamp((obj_bbox.x1 - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
		int iymax = clamp((obj_bbox.y1 - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
		int izmax = clamp((obj_bbox.z1 - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);

		// add the object to the cells:
		for (int iz(izmin); iz <= izmax; iz++) {// cells in z direction
			for (int iy(iymin); iy <= iymax; iy++) {// cells in y direction
				for (int ix(ixmin); ix <= ixmax; ix++) { // cells in x direction

					index = ix + nx * iy + nx * ny * iz;

					if (counts[index] == 0) {
						
						cells[index] = objects[i];
						counts[index] += 1;
					}
					else {
						
						if (counts[index] == 1) {
							
							// construct a compound object
							Compound* compound_ptr = new Compound;
							// add the object already in cell
							compound_ptr->add_object(cells[index]);
							// add the new object
							compound_ptr->add_object(objects[i]);
							// store compound in current cell
							cells[index] = compound_ptr;
							// index = 2
							counts[index]++;
						}
						else { // counts[index] > 1
							// just add current object
							cells[index]->add_object(objects[i]);
							// for statistics only
							counts[index] ++;
						}
					}
				}
			}
		}
	}
	// erase Compound::Objects, but don?t delete the objects
	objects.erase(objects.begin(), objects.end());

	// code for statistics on cell objects counts can go in here
	// erase the temporary counts vector
	counts.erase(counts.begin(), counts.end());
}

bool
Grid::hit(const Ray& raymond, double& tmin, ShadeRec& sr) const 
{
	double ox = raymond.o.x;
	double oy = raymond.o.y;
	double oz = raymond.o.z;
	double dx = raymond.d.x;
	double dy = raymond.d.y;
	double dz = raymond.d.z;

	double x0 = bbox.x0;
	double y0 = bbox.y0;
	double z0 = bbox.z0;
	double x1 = bbox.x1;
	double y1 = bbox.y1;
	double z1 = bbox.z1;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	if (t0 > t1)
		return false;

	// initial cell coordinates

	int ix, iy, iz;

	if (bbox.inside(raymond.o)) {  			// does the ray start inside the grid?
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else {
		Point3D p = raymond.o + t0 * raymond.d;  // initial hit point with grid's bounding box
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}

	// ray parameter increments per cell in the x, y, and z directions

	double dtx = (tx_max - tx_min) / nx;
	double dty = (ty_max - ty_min) / ny;
	double dtz = (tz_max - tz_min) / nz;

	double 	tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;

	if (dx > 0) {
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else {
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dx == 0.0) {
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dy > 0) {
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dy == 0.0) {
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dz > 0) {
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}

	if (dz == 0.0) {
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}

	// traverse the grid

	while (true) {
		GeometricObject* object_ptr = cells[ix + nx * iy + nx * ny * iz];

		if (tx_next < ty_next && tx_next < tz_next) {
			if (object_ptr && object_ptr->hit(raymond, tmin, sr) && tmin < tx_next) {
				material_ptr = object_ptr->get_material();
				return true;
			}

			tx_next += dtx;
			ix += ix_step;

			if (ix == ix_stop)
				return false;
		}
		else {
			if (ty_next < tz_next) {
				if (object_ptr && object_ptr->hit(raymond, tmin, sr) && tmin < ty_next) {
					material_ptr = object_ptr->get_material();
					return true;
				}

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop)
					return false;
			}
			else {
				if (object_ptr && object_ptr->hit(raymond, tmin, sr) && tmin < tz_next) {
					material_ptr = object_ptr->get_material();
					return true;
				}

				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop)
					return false;
			}
		}
	}
}

bool 
Grid::shadow_hit(const Ray& raymond, double& tmin) const 
{
	double ox = raymond.o.x;
	double oy = raymond.o.y;
	double oz = raymond.o.z;
	double dx = raymond.d.x;
	double dy = raymond.d.y;
	double dz = raymond.d.z;

	double x0 = bbox.x0;
	double y0 = bbox.y0;
	double z0 = bbox.z0;
	double x1 = bbox.x1;
	double y1 = bbox.y1;
	double z1 = bbox.z1;

	double tx_min, ty_min, tz_min;
	double tx_max, ty_max, tz_max;

	double a = 1.0 / dx;
	if (a >= 0) {
		tx_min = (x0 - ox) * a;
		tx_max = (x1 - ox) * a;
	}
	else {
		tx_min = (x1 - ox) * a;
		tx_max = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0) {
		ty_min = (y0 - oy) * b;
		ty_max = (y1 - oy) * b;
	}
	else {
		ty_min = (y1 - oy) * b;
		ty_max = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0) {
		tz_min = (z0 - oz) * c;
		tz_max = (z1 - oz) * c;
	}
	else {
		tz_min = (z1 - oz) * c;
		tz_max = (z0 - oz) * c;
	}

	double t0, t1;

	if (tx_min > ty_min)
		t0 = tx_min;
	else
		t0 = ty_min;

	if (tz_min > t0)
		t0 = tz_min;

	if (tx_max < ty_max)
		t1 = tx_max;
	else
		t1 = ty_max;

	if (tz_max < t1)
		t1 = tz_max;

	if (t0 > t1)
		return false;

	// initial cell coordinates

	int ix, iy, iz;

	if (bbox.inside(raymond.o)) {  			// does the ray start inside the grid?
		ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
	}
	else {
		Point3D p = raymond.o + t0 * raymond.d;  // initial hit point with grid's bounding box
		ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
		iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
		iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
	}

	// ray parameter increments per cell in the x, y, and z directions

	double dtx = (tx_max - tx_min) / nx;
	double dty = (ty_max - ty_min) / ny;
	double dtz = (tz_max - tz_min) / nz;

	double 	tx_next, ty_next, tz_next;
	int ix_step, iy_step, iz_step;
	int ix_stop, iy_stop, iz_stop;

	if (dx > 0) {
		tx_next = tx_min + (ix + 1) * dtx;
		ix_step = +1;
		ix_stop = nx;
	}
	else {
		tx_next = tx_min + (nx - ix) * dtx;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dx == 0.0) {
		tx_next = kHugeValue;
		ix_step = -1;
		ix_stop = -1;
	}

	if (dy > 0) {
		ty_next = ty_min + (iy + 1) * dty;
		iy_step = +1;
		iy_stop = ny;
	}
	else {
		ty_next = ty_min + (ny - iy) * dty;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dy == 0.0) {
		ty_next = kHugeValue;
		iy_step = -1;
		iy_stop = -1;
	}

	if (dz > 0) {
		tz_next = tz_min + (iz + 1) * dtz;
		iz_step = +1;
		iz_stop = nz;
	}
	else {
		tz_next = tz_min + (nz - iz) * dtz;
		iz_step = -1;
		iz_stop = -1;
	}

	if (dz == 0.0) {
		tz_next = kHugeValue;
		iz_step = -1;
		iz_stop = -1;
	}

	// traverse the grid

	while (true) {
		GeometricObject* object_ptr = cells[ix + nx * iy + nx * ny * iz];

		if (tx_next < ty_next && tx_next < tz_next) {
			if (object_ptr && object_ptr->shadow_hit(raymond, tmin) && tmin < tx_next)
				return true;

			tx_next += dtx;
			ix += ix_step;

			if (ix == ix_stop)
				return false;
		}
		else {
			if (ty_next < tz_next) {
				if (object_ptr && object_ptr->shadow_hit(raymond, tmin) && tmin < ty_next)
					return true;

				ty_next += dty;
				iy += iy_step;

				if (iy == iy_stop)
					return false;
			}
			else {
				if (object_ptr && object_ptr->shadow_hit(raymond, tmin) && tmin < tz_next)
					return true;

				tz_next += dtz;
				iz += iz_step;

				if (iz == iz_stop)
					return false;
			}
		}
	}
}

Point3D
Grid::min_coordinates() 
{
	BBox obj_bbox;
	Point3D p0(kHugeValue);

	int num_objects = this->objects.size();

	for (int i(0); i < num_objects; i++) {
		
		obj_bbox = objects[i]->get_bounding_box();

		if (obj_bbox.x0 < p0.x)
			p0.x = obj_bbox.x0;

		if (obj_bbox.y0 < p0.y)
			p0.y = obj_bbox.y0;

		if (obj_bbox.z0 < p0.z)
			p0.z = obj_bbox.z0;
	}

	p0.x -= kEpsilon;
	p0.y -= kEpsilon;
	p0.z -= kEpsilon;

	return p0;
}

Point3D
Grid::max_coordinates() 
{
	BBox obj_bbox;
	Point3D p1(-kHugeValue);

	int num_objects = this->objects.size();

	for (int i(0); i < num_objects; i++) {

		obj_bbox = objects[i]->get_bounding_box();

		if (obj_bbox.x1 > p1.x)
			p1.x = obj_bbox.x1;

		if (obj_bbox.y1 > p1.y)
			p1.y = obj_bbox.y1;

		if (obj_bbox.z1 > p1.z)
			p1.z = obj_bbox.z1;
	}

	p1.x += kEpsilon;
	p1.y += kEpsilon;
	p1.z += kEpsilon;

	return p1;
}
