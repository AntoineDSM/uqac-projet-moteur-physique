#pragma once

#include "Vector3D/Vector3D.h"
#include "Quaternion.h"
#include "Matrix34.h"

class RigidBody {

private:
	// same as for Particle
	float inverseMasse;
	float linearDamping;
	Vector3D position;
	Vector3D velocity;
	// Orientation of the rigid body
	Quaternion orientation;
	// Angular velocity of the rigid body
	Vector3D rotation;
	// calculates transform matrix from orientation and rotation
	Matrix34 transformMatrix;
public:
	// Integrate the rigid body by modifying position, orientation and velocities.
	void Integrate(float duration);
private:
	// call each frame to calculate the transformMatrix and normalize the orientation.
	void CalculateDerivedData();
};