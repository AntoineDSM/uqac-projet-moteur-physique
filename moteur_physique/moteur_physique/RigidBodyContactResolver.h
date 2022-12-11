#pragma once

#ifndef CONTACT_RIGIDBODY_RESOLVER
#define CONTACT_RIGIDBODY_RESOLVER

#include "ContactRigidBody.h"

class RigidBodyContactResolver
{
protected:
	unsigned int m_iteration;

public:

	RigidBodyContactResolver() = default;

	void resolveContacts(ContactRigidBody* contactArray,
		unsigned int numContact,
		float duration);
};

#endif CONTACT_RIGIDBODY_RESOLVER

