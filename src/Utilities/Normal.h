#pragma once

#include "Matrix_4.h"
#include "Vector3D.h"
#include "Point3D.h"

class Normal {	
public:
	
	// component
	double	x, y, z;
	
	// default constructor
	Normal();

	// scalar constructor
	Normal(double a);

	// component constructor
	Normal(double _x, double _y, double _z);

	// copy constructor
	Normal(const Normal& n);

	// constructs a normal from vector
	Normal(const Vector3D& v);

	// assignment operator
	Normal& operator= (const Normal& rhs); 	
	
	// assignment of a vector to a normal
	Normal& operator= (const Vector3D& rhs);
		
	// assignment of a point to a normal
	Normal& operator= (const Point3D& rhs);
		
	// negation
	Normal operator- () const;	
		
	// addition
	Normal operator+ (const Normal& n) const;
		
	// in-place addition
	Normal& operator+= (const Normal& n);
	
	// dot product by vector on the right
	double operator* (const Vector3D& v) const;
	
	// multiplication by a double on the right
	Normal operator* (const double a) const;
	
	// set length to 1.0
	void normalize(); 									 		
};


inline Normal 											
Normal::operator- () const 
{
	return Normal(-x, -y, -z);
}

inline Normal 											
Normal::operator+ (const Normal& n) const 
{
	return Normal(x + n.x, y + n.y, z + n.z);
}

inline Normal& 
Normal::operator+= (const Normal& n) 
{
	x += n.x; y += n.y; z += n.z;
    return *this;
}

inline double
Normal::operator* (const Vector3D& v) const 
{
	return x * v.x + y * v.y + z * v.z;
}

inline Normal
Normal::operator* (const double a) const 
{
	return Normal(x * a, y * a, z * a);
}

// non member functions:

// multiplication by double on the left
inline Normal
operator*(const double f, const Normal& n) 
{
	return Normal(f * n.x, f * n.y,f * n.z);
}

// addition of a vector on the left to return a vector 
inline Vector3D
operator+ (const Vector3D& v, const Normal& n) 
{	
	return Vector3D(v.x + n.x, v.y + n.y, v.z + n.z);
}	

// subtraction of a normal from a vector to return a vector
inline Vector3D
operator- (const Vector3D& v, const Normal& n) 
{
	return Vector3D(v.x - n.x, v.y - n.y, v.z - n.z);
}

// dot product of a vector on the left and a normal on the right
inline double
operator* (const Vector3D& v, const Normal& n) 
{
	return (v.x * n.x + v.y * n.y + v.z * n.z);     
}

// multiplication by a matrix on the left
Normal 											
operator* (const Matrix_4& mat, const Normal& n);
