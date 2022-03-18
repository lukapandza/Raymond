#pragma once

// this file contains the declaration of the class Matrix
// Matrix is a 4 x 4 square matrix that is used to represent affine transformations
// we don't need a general m x n matrix

//----------------------------------------- class Matrix

class Matrix_4 {
	
public:
	
	double	m[4][4]; // elements
	
		
	Matrix_4(); // default constructor

	Matrix_4(const Matrix_4& mat); // copy constructor
		
	~Matrix_4 (); // destructor
			
	Matrix_4& // assignment operator
		operator= (const Matrix_4& rhs); 	
			
	Matrix_4 // multiplication of two matrices
		operator* (const Matrix_4& mat) const;

	Matrix_4 // divsion by a double
		operator/ (const double d);

	void // set to the identity matrix
		set_identity();	
};
