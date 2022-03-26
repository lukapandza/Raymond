#pragma once

#include "Matrix_4.h"
class Normal; // forward decleration
class Point3D; // forward decleration
#include "Maths.h"

class Vector3D {
public:
	
	// component
	double	x, y, z;
	
	// default constructor
	Vector3D();

	// scalar constructor
	Vector3D(double a);							

	// component constructor
	Vector3D(double _x, double _y, double _z);

	// copy constructor
	Vector3D(const Vector3D& v);

	// constructs a vector from a Normal
	Vector3D(const Normal& n);

	// constructs a vector from a point
	Vector3D(const Point3D& p);

	// assignment operator
	Vector3D& operator= (const Vector3D& rhs);
	
	// assign a Normal to a vector
	Vector3D& operator= (const Normal& rhs); 
		
	// assign a Point3D to a vector
	Vector3D& operator= (const Point3D& rhs); 
		
	// negation
	Vector3D operator- () const;									
	
	// length of vector
	double length();
	
	// square of the length
	double len_squared();
	
	// multiplication by a double on the right
	Vector3D operator* (const double a) const;

	// in-place multiplication by a double on the right
	Vector3D& operator*= (const double a);
	
	// division by a double
	Vector3D operator/ (const double a) const;
		
	// addition
	Vector3D operator+ (const Vector3D& v) const;
	
	// in-place addition
	Vector3D& operator+= (const Vector3D& v);					
	
	// subtraction
	Vector3D operator- (const Vector3D& v) const;					
		
	// dot product
	double operator* (const Vector3D& b) const;
		
	// cross product
	Vector3D operator^ (const Vector3D& v) const;
		
	// convert vector to a unit vector
	void normalize(); 
	
	// return a unit vector, and normalize the vector in place
	Vector3D& hat();
};


inline Vector3D 
Vector3D::operator- () const 
{
	return Vector3D(-x, -y, -z);    
}

inline double
Vector3D::length()
{
	return sqrt(x * x + y * y + z * z);
}

inline double													
Vector3D::len_squared() 
{	
	return x * x + y * y + z * z;
}

inline Vector3D
Vector3D::operator* (const double a) const 
{	
	return Vector3D(x * a, y * a, z * a);	
}

inline Vector3D&
Vector3D::operator*= (const double a)
{
	x *= a; y *= a; z *= a;
	return *this;
}

inline Vector3D
Vector3D::operator/ (const double a) const 
{	
	double inv_a = 1.0 / a;
	return Vector3D(x * inv_a, y * inv_a, z * inv_a);	
}

inline Vector3D
Vector3D::operator+ (const Vector3D& v) const 
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

inline Vector3D
Vector3D::operator- (const Vector3D& v) const 
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

inline double 
Vector3D::operator* (const Vector3D& v) const 
{
	return x * v.x + y * v.y + z * v.z;
} 

inline Vector3D 									
Vector3D::operator^ (const Vector3D& v) const 
{
	return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

inline void
Vector3D::normalize()
{
	double inv_length = 1.0 / this->length();
	//double inv_length = fast_inv_sqrt(x * x + y * y + z * z);
	x *= inv_length; y *= inv_length; z *= inv_length;
}

inline Vector3D&
Vector3D::hat()
{
	*this *= 1.0 / this->length();
	//*this *= fast_inv_sqrt(this->len_squared());
	return *this;
}

inline Vector3D& 
Vector3D::operator+= (const Vector3D& v) 
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}


// non-member functions: 

// multiplication by a double on the left
inline Vector3D 
operator* (const double a, const Vector3D& v) 
{
	return Vector3D(a * v.x, a * v.y, a * v.z);	
}

// multiplication by a matrix on the left
Vector3D operator* (const Matrix_4& mat, const Vector3D& v);
