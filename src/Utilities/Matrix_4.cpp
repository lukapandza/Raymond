#include "Matrix_4.h"

Matrix_4::Matrix_4() 
{	
	// by default we construct an identity matrix
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}

Matrix_4::Matrix_4 (const Matrix_4& mat) 
{
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = mat.m[x][y];	
}

Matrix_4& 
Matrix_4::operator= (const Matrix_4& rhs) 
{
	if (this == &rhs)
		return *this;

	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = rhs.m[x][y];	

	return *this;
}

Matrix_4 
Matrix_4::operator* (const Matrix_4& mat) const 
{
	Matrix_4 product;
	
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
				sum += m[x][j] * mat.m[j][y];
 
			product.m[x][y] = sum;			
		}
	
	return product;
}

Matrix_4 
Matrix_4::operator/ (const double d) 
{
	for (int x = 0; x < 4; x++)				
		for (int y = 0; y < 4; y++)			
			m[x][y] = m[x][y] / d;	

	return *this;
}

void											
Matrix_4::set_identity() 
{
    for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++) {
			if (x == y)
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}
