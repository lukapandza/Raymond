#include "GlossySpecular.h"

// default constructor
GlossySpecular::GlossySpecular(void) 
	: BRDF(),
	ks(1.0),
	cs(1.0),
	exp(16.0)
{}

//copy constructor
GlossySpecular::GlossySpecular(const GlossySpecular& rhs) 
	: BRDF(rhs),
	ks(rhs.ks),
	cs(rhs.cs),
	exp(rhs.exp)
{}

// clone
GlossySpecular*
GlossySpecular::clone(void) const {
	return new GlossySpecular(*this);
}

// destructor
GlossySpecular::~GlossySpecular(void) {
	BRDF::~BRDF();
}

// assignment operator
GlossySpecular&
GlossySpecular::operator= (const GlossySpecular& rhs) {

	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);

	ks = rhs.ks;
	cs = rhs.cs;
	exp = rhs.exp;

	return *this;
}

RGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const {
	
	RGBColor L;
	double  n_dot_w_i = sr.normal * w_i;
	Vector3D r(-w_i + 2.0 * sr.normal * n_dot_w_i);
	double  r_dot_w_o = r * w_o;

	if (r_dot_w_o > 0.0)
		L = ks * pow(r_dot_w_o, exp);

	return L;
}

RGBColor
GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i) const {
	
	double  n_dot_wo = sr.normal * w_o;

	// reflection:
	Vector3D w = -w_o + 2.0 * sr.normal * n_dot_wo; // direction of perfect mirror reflection
	Vector3D u = Vector3D(0.00024, 1, 0.00064) ^ w;
	u.normalize();
	Vector3D v = u ^ w;

	Point3D sp = this->sampler_ptr->sample_hemisphere();
	w_i = sp.x * u + sp.y * v + sp.z * w; // reflected ray direction
	if (sr.normal * w_i < 0.0) // reflected ray is below surface
		w_i = -sp.x * u - sp.y * v + sp.z * w;
	w_i.normalize();

	return this->ks * this->cs;
}

RGBColor
GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double& pdf) const {
	
	double  n_dot_wo = sr.normal * w_o;
	Vector3D r = -w_o + 2.0 * sr.normal * n_dot_wo; // direction of mirror

	// reflection
	Vector3D w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.normalize();
	Vector3D v = u ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();

	w_i = sp.x * u + sp.y * v + sp.z * w; // reflected ray direction
	if (sr.normal * w_i < 0.0) // reflected ray is below surface
		w_i = -sp.x * u - sp.y * v + sp.z * w;

	double  phong_lobe = pow(r * w_i, exp);
	pdf = phong_lobe * (sr.normal * w_i);

	return (ks * cs * phong_lobe);
}