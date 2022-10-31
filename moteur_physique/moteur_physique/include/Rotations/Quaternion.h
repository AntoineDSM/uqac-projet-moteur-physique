#pragma once
#include "Vector3D/Vector3D.h"

using namespace moteurJeux;

class Quaternion
{
private:
	// w, i,j,k

	float value[4];


public:

	float w, i, j, k;

	//quaternion de base
	Quaternion() : w(1), i(0), j(0), k(0) {}



	// normalize by multipling the quaternion by the inverse of its magnitude
	void Normalized();
	// Quaternion multiplication
	Quaternion operator* (const Quaternion& other);
	// Rotate the quaternion by a vector -multiply this by q = (e, dx, dy, dz)
	void RotateByVector(const Vector3D& vector);
	// Apply the quaternion update by the angular velcity
	void UpdateByAngularVelocity(const Vector3D& rotation, float duration);
};