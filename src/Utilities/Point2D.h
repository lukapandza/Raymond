#pragma once

// 2D points are used to store sample points
class Point2D {	
public:
	
	// component
	double x, y;
	
	// default constructor
	Point2D();

	// scalar constructor
	Point2D(const double arg);

	// component constructor
	Point2D(const double x1, const double y1);

	// copy constructor
	Point2D(const Point2D& p);

	// assignmnet operator
	Point2D& operator= (const Point2D& rhs);
	
	// multiplication by scalar on the right
	Point2D	operator* (const double a);
};

inline Point2D
Point2D::operator* (const double a) 
{
	return Point2D(x * a, y * a);
}
