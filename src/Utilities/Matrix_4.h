#pragma once

// 4x4 square matrix for affine transformations
// a general MxN matrix is not needed
class Matrix_4 {
	
public:
	
	// elements
	double	m[4][4];
	
	// default constructor
	Matrix_4(); 

	// copy constructor
	Matrix_4(const Matrix_4& mat);
	
	// assignment operator
	Matrix_4& operator= (const Matrix_4& rhs); 	
			
	// multiplication of two matrices
	Matrix_4 operator* (const Matrix_4& mat) const;

	// divsion by a double
	Matrix_4 operator/ (const double d);

	// set to the identity matrix
	void set_identity();	
};
