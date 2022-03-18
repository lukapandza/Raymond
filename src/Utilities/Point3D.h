#pragma once

#include "Matrix_4.h"
#include "Vector3D.h"

class Point3D {
public:
	
	// component
	double x, y, z;
	
	// default constructor
	Point3D();

	// scalar constructor
	Point3D(const double a);

	// component constructor
	Point3D(const double a, const double b, const double c);

	// copy constructor
	Point3D(const Point3D& p);
		
	// assignment operator
	Point3D& operator= (const Point3D& p);
		
	// negation
	Point3D operator- () const;
	
	// vector joining two points
	Vector3D operator- (const Point3D& p) const;
		
	// addition of a vector	
	Point3D operator+ (const Vector3D& v) const;
		
	// subtraction of a vector
	Point3D operator- (const Vector3D& v) const;
				
	// multiplication by a double on the right
	Point3D operator* (const double a) const;
		
	// square of distance bertween two points
	double d_squared(const Point3D& p) const;
		
	// distance bewteen two points
	double distance(const Point3D& p) const;
};


inline Point3D 
Point3D::operator- (void) const 
{
	return Point3D(-x, -y, -z);
}

inline Vector3D 
Point3D::operator- (const Point3D& p) const 
{
	return Vector3D(x - p.x,y - p.y,z - p.z);
}

inline Point3D 
Point3D::operator+ (const Vector3D& v) const 
{
	return Point3D(x + v.x, y + v.y, z + v.z);
}

inline Point3D 
Point3D::operator- (const Vector3D& v) const 
{
	return Point3D(x - v.x, y - v.y, z - v.z);
}

inline Point3D 
Point3D::operator* (const double a) const 
{
	return Point3D(x * a,y * a,z * a);
}

inline double
Point3D::d_squared(const Point3D& p) const 
{
	return 	(x - p.x) * (x - p.x) 
		+ 	(y - p.y) * (y - p.y)
		+	(z - p.z) * (z - p.z);
}

// non member functions: 

// multiplication by scalar on the left
inline Point3D
operator* (double a, const Point3D& p) 
{
	return Point3D(a * p.x, a * p.y, a * p.z);
}

// multiplication by a matrix on the left
Point3D 						
operator* (const Matrix_4& mat, const Point3D& p);

