#include "Torus.h"
#include "../Utilities/Maths.h"

Torus::Torus() 
	: a(2),
	b(0.5),
	box(-a - b, -b, -a - b, a + b, b, a + b),
	inv_area(1.0 / 4.0 * PI * PI * a * b),
	sampler_ptr(nullptr)
{}

Torus::Torus(const double _a, const double _b) 
	: a(_a),
	b(_b),
	box(-a - b, -b, -a - b, a + b, b, a + b),
	inv_area(1.0 / 4.0 * PI * PI * a * b),
	sampler_ptr(nullptr)
{}

Torus::Torus(const Torus& rhs) 
	: a(rhs.a),
	b(rhs.b),
	box(rhs.box),
	inv_area(rhs.inv_area),
	sampler_ptr(sampler_ptr)
{}

Torus*
Torus::clone() const 
{
	return new Torus(*this);
}

Torus&
Torus::operator=(const Torus& rhs) 
{
	if (this == &rhs)
		return *this;

	a = rhs.a;
	b = rhs.b;
	box = rhs.box;
	inv_area = rhs.inv_area;
	sampler_ptr = rhs.sampler_ptr;

	return *this;
}

Torus::~Torus() 
{
	delete sampler_ptr;
}

Normal
Torus::compute_normal(const Point3D& p) const 
{
	Normal normal;
	double param_squared = a * a + b * b;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;

	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.normalize();

	return normal;
}

bool
Torus::hit(const Ray& raymond, double& tmin, ShadeRec& sr) const 
{
	if (!box.hit(raymond))
		return false;

	double x1 = raymond.o.x;
	double y1 = raymond.o.y;
	double z1 = raymond.o.z;

	double d1 = raymond.d.x;
	double d2 = raymond.d.y;
	double d3 = raymond.d.z;

	double coeffs[5];
	double roots[4];

	double sum_d_squared = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_squared = 4.0 * a * a;

	coeffs[0] = e * e - four_a_squared * (b * b - y1 * y1);
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_squared * y1 * d2;
	coeffs[2] = 2.0 * sum_d_squared * e + 4.0 * f * f + four_a_squared * d2 * d2;
	coeffs[3] = 4.0 * sum_d_squared * f;
	coeffs[4] = sum_d_squared * sum_d_squared;

	int num_real_roots = solve_quartic(coeffs, roots);

	bool intersected = false;
	double t = kHugeValue;

	if (num_real_roots == 0)
		return false;

	for (int i = 0; i < num_real_roots; i++) {
		if (roots[i] > kEpsilon) {
			intersected = true;
			if (roots[i] < t)
				t = roots[i];
		}
	}

	if (!intersected)
		return false;

	tmin = t;
	sr.local_hit_point = raymond.o + t * raymond.d;
	sr.normal = compute_normal(sr.local_hit_point);

	return true;
}

bool
Torus::shadow_hit(const Ray& raymond, double& tmin) const 
{
	if (!box.hit(raymond))
		return false;

	double x1 = raymond.o.x;
	double y1 = raymond.o.y;
	double z1 = raymond.o.z;

	double d1 = raymond.d.x;
	double d2 = raymond.d.y;
	double d3 = raymond.d.z;

	double coeffs[5];
	double roots[4];

	double sum_d_squared = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_squared = 4.0 * a * a;

	coeffs[0] = e * e - four_a_squared * (b * b - y1 * y1);
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_squared * y1 * d2;
	coeffs[2] = 2.0 * sum_d_squared * e + 4.0 * f * f + four_a_squared * d2 * d2;
	coeffs[3] = 4.0 * sum_d_squared * f;
	coeffs[4] = sum_d_squared * sum_d_squared;

	int num_real_roots = solve_quartic(coeffs, roots);

	bool intersected = false;
	double t = kHugeValue;

	if (num_real_roots == 0)
		return false;

	for (int i = 0; i < num_real_roots; i++) {
		if (roots[i] > kEpsilon) {
			intersected = true;
			if (roots[i] < t)
				t = roots[i];
		}
	}

	if (!intersected)
		return false;

	tmin = t;

	return true;
}
