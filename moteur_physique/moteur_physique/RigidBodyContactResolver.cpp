#include "RigidBodyContactResolver.h"

void RigidBodyContactResolver::resolveContacts(ContactRigidBody* contactArray, unsigned int numContact, float duration)
{
	if (numContact == 0) return;
	m_iteration = 0;
	float smallestRelativeVelocity = 1000;
	while (m_iteration < numContact) {
		ContactRigidBody* contactToResolve = nullptr;
		for (int i = 0; i < numContact; i++) {
			float currentVel = (contactArray + i)->calculateSeperatingVelocity();
			if (currentVel < smallestRelativeVelocity) {
				smallestRelativeVelocity = currentVel;
				contactToResolve = (contactArray + i);
			}
		}
		if (contactToResolve == nullptr) {
			contactToResolve = (contactArray);
		}
		contactToResolve->resolve(duration);

		m_iteration++;
	}
}