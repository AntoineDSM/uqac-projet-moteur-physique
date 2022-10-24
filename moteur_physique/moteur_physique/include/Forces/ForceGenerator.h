#pragma once

#include "Rotations/RigidBody.h"
class ForceGenerator {
public:
	// Apply force to the rigidBody
	virtual void UpdateForce(RigidBody* rigidBody) = 0;

};