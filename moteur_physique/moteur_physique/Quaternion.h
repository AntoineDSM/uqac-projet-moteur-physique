#pragma once
#include "Vector3D.h"

using namespace moteurJeux;

class Quaternion
{
private:
	// w, i,j.k
	float value[4];
public:
	// normalize by multipling the quaternion by the inverse of its magnitude
	void Normalized();
	// Quaternion multiplication
	Quaternion operator* (const Quaternion& other);
	// Rotate the quaternion by a vector -multiply this by q = (e, dx, dy, dz)
	void RotateByVector(const Vector3D& vector);
	// Apply the quaternion update by the angular velcity
	void UpdateByAngularVelocity(const Vector3D& rotation, float duration);
};