#include "PhongBRDF.h"

// default constructor
PhongBRDF::PhongBRDF()
	: BRDF(),
	k_d(.5),
	c_d(1.0),
	k_s(.5),
	exp(16.0),
	c_s(1.0),
	sampler_ptr_d(nullptr),
	sampler_ptr_s(nullptr)
{}

// copy constructor
PhongBRDF::PhongBRDF(const PhongBRDF& rhs)
	: BRDF(rhs),
	k_d(rhs.k_d),
	c_d(rhs.c_d),
	k_s(rhs.k_s),
	exp(rhs.exp),
	c_s(rhs.c_s),
	sampler_ptr_d(nullptr),
	sampler_ptr_s(nullptr)
{
	if (rhs.sampler_ptr_d)
		this->sampler_ptr_d = rhs.sampler_ptr_d->clone();

	if (rhs.sampler_ptr_s)
		this->sampler_ptr_s = rhs.sampler_ptr_s->clone();
}

// clone
PhongBRDF*
PhongBRDF::clone() const 
{
	return new PhongBRDF(*this);
}

// destructor
PhongBRDF::~PhongBRDF() 
{
	if (this->sampler_ptr_d)
		delete this->sampler_ptr_d;

	if (this->sampler_ptr_s)
		delete this->sampler_ptr_s;

	BRDF::~BRDF();
}

// assignment operator
PhongBRDF&
PhongBRDF::operator= (const PhongBRDF& rhs) 
{
	if (this == &rhs)
		return *this;

	BRDF::operator=(rhs);

	this->k_d = rhs.k_d;
	this->c_d = rhs.c_d;
	this->k_s = rhs.k_s;
	this->exp = rhs.exp;
	this->c_s = rhs.c_s;

	if (this->sampler_ptr_d) {
		delete this->sampler_ptr_d;
		this->sampler_ptr_d = nullptr;
	}

	if (rhs.sampler_ptr_d)
		this->sampler_ptr_d = rhs.sampler_ptr_d->clone();

	if (this->sampler_ptr_s) {
		delete this->sampler_ptr_s;
		this->sampler_ptr_s = nullptr;
	}

	if (rhs.sampler_ptr_s)
		this->sampler_ptr_s = rhs.sampler_ptr_s->clone();

	return *this;
}

// functions:
RGBColor
PhongBRDF::f(const ShadeRec& sr, const Vector3D& w_i, const Vector3D& w_o) const
{
	Vector3D r(-w_i + 2.0 * sr.normal * (sr.normal * w_i));
	double  r_dot_w_o = r * w_o;

	return this->c_d * this->k_d * invPI
		+ this->c_s * this->k_s * (this->exp + 2) * invTWO_PI * (r_dot_w_o > 0 ? pow(r_dot_w_o, this->exp) : 0.0);
}

RGBColor
PhongBRDF::sample_f(const ShadeRec& sr, Vector3D& w_i, const Vector3D& w_o) const {
	return black;
}

RGBColor
PhongBRDF::sample_f(const ShadeRec& sr, const Vector3D& w_o, Vector3D& w_i, double& pdf) const {
	
	Point3D sp;
	Vector3D u, v, w;

	// diffuse contriution:
	w = sr.normal;
	v = Vector3D(0.0034, 1.0, 0.0063) ^ w;
	v.normalize();
	u = v ^ w;

	sp = this->sampler_ptr_d->sample_hemisphere();
	Vector3D w_i_d = sp.x * u + sp.y * v + sp.z * w;
	w_i_d.normalize();


	// specular contribution:
	double  n_dot_wo = sr.normal * w_o;

	// reflection:
	w = -w_o + 2.0 * sr.normal * n_dot_wo; // direction of perfect mirror reflection
	u = Vector3D(0.00024, 1, 0.00064) ^ w;
	u.normalize();
	v = u ^ w;

	sp = this->sampler_ptr_s->sample_hemisphere();

	Vector3D w_i_s = sp.x * u + sp.y * v + sp.z * w; // reflected ray direction
	if (sr.normal * w_i_s < 0.0) // reflected ray is below surface
		w_i_s = -sp.x * u - sp.y * v + sp.z * w;
	w_i_s.normalize();


	double rand = rand_float(0, 1.0);
	double p_d = this->k_d / (this->k_d + this->k_s);
	double p_s = this->k_s / (this->k_d + this->k_s);

	w_i = rand < p_d ? w_i_d : w_i_s;
	
	//return this->k_d * this->c_d + this->k_s * this->c_s;
	return p_d * this->c_d + p_s * this->c_s;
}

RGBColor
PhongBRDF::rho(const ShadeRec& sr, const Vector3D& w_o) const {
	return black;
}
