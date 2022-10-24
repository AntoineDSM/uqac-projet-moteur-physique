#pragma once

#pragma once
#include "Vector3D/Vector3D.h"
#include "Quaternion.h"

class Matrix34
{
private:
	// values of the Matrix 3X4
	float values[12];

public:
	// combination of affine transformation
	Matrix34 operator* (const Matrix34& other) const;
	// Transform of a vector
	Vector3D operator* (const Vector3D& vector) const;
	// Get the Inverse matrix
	Matrix34 Inverse();
	// Set the matrix base on a quaternion and a position
	void SetOrientationAndPosition(const Quaternion& q, const Vector3D& p);
	// Transform a position
	Vector3D TransformPosition(const Vector3D& vector);
	// Transform a direction by ignoring the translation
	Vector3D TransformDirection(const Vector3D& vector);

};