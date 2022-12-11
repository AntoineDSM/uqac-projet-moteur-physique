#pragma once
#include <vector>
#include "RigidBodyContact.h"

class RigidBodyContactResolver
{
protected:
	unsigned int m_iteration;

public:

	RigidBodyContactResolver() = default;

	void resolveContacts(RigidBodyContact* contactArray,
		unsigned int numContact,
		float duration);
};

