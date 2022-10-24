#pragma once

#include "Forces/ForceGenerator.h"
#include "Vector3D/Vector3D.h"
#include "Rotations/RigidBody.h"

class GravityForceGenerator : public ForceGenerator
{
	
	private:
		Vector3D m_gravity;
		Vector3D m_gravity;
	public:
		// Apply the gravity force to center of mass of the rigidBody
		void UpdateForce(RigidBody * rigidBody) override;
};

