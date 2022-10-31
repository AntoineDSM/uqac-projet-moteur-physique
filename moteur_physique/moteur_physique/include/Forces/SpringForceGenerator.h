#pragma once

#include "Vector3D/Vector3D.h"
#include "Rotations/RigidBody.h"
#include "Forces/ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator {
private:
	// Anchor point in Local coordinate.
	Vector3D m_bodyAnchor;
	RigidBody* m_otherRigidBody = nullptr;
	// Other anchor point in other's Local coordinate.
	Vector3D m_otherBodyAnchor;
	// spring parameters
	float m_k;
	float m_restLength;
public:
	// Transform each anchor point in world coordinate,
	// calculate the spring force and apply it at anchor point.
	void UpdateForce(RigidBody* rigidBody) override;

};