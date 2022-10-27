#pragma once
#include "Vector3D/Vector3D.h"
#include "Quaternion.h"
class Matrix33
{
private:
	// values of the Matrix 3X3
	float values[9];
public:
	// combination of linear transformation
	Matrix33 operator*(const Matrix33& other) const;
	// Transform of a vector
	Vector3D operator* (const Vector3D& vector) const;
	// Get the Inverse matrix
	Matrix33 Inverse( );

	// Get the Transpose matrix
	Matrix33 Transpose();


	// Set the matrix base on a quaternion
	void Set0rientation(const Quaternion& q);
};