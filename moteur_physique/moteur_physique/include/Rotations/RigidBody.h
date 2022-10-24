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

	//same as linear damping but for rotation
	float m_angularDamping;
	// Accumulated force added by ForceGenerator
	Vector3D m_forceAccum;
	// Accumulated torque added by ForceGenerator
	Vector3D m_torqueAccum;

public:
	// Integrate the rigid body by modifying position, orientation and velocities.
	void Integrate(float duration);

public:
	// Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3D& force);
	// Add force at a point in world coordinate.
	// Generate force and torque
	void AddForceAtPoint(const Vector3D& force, const Vector3D& worldPoint);
	// Add force at a point in local coordinate.
	// the point is converted in world coordinated by using the transform matrix.
	// Generate force and torque
	void AddForceAtBodyPoint(const Vector3D& force, const Vector3D& LocalPoint);
	// called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();

private:
	// call each frame to calculate the transformMatrix and normalize the orientation.
	void CalculateDerivedData();
};