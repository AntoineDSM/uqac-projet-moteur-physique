#pragma once

#pragma once
#include "Vector3D/Vector3D.h"
#include "Quaternion.h"

class Matrix34
{
private:
	
public:

	// values of the Matrix 3X4
	float values[12];

	//Constructeur de matrice 3x4 identité
	Matrix34()
	{
		
		for (int i = 0; i < 12; i++) {
			if (i % 5 == 0) {
				values[i] = 1;
			}
			else {
				values[i] = 0;
			}
		}
		
	}

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