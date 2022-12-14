#pragma once

#ifndef CONTACT_RIGIDBODY_RESOLVER
#define CONTACT_RIGIDBODY_RESOLVER

#include "ContactRigidBody.h"

//Non utilisee, aurait permis de resoudre les contacts par ordre de priorite comme pour le systeme de particules.
//nous resolvons tous les contacts dans l'ordre de reception et d'insertion en liste, pas de priorisation pour les rigidbodies.
class RigidBodyContactResolver
{

private:

	unsigned int m_iteration;

public:

	RigidBodyContactResolver();

	void resolveContacts(ContactRigidBody* contactArray, unsigned int numContact, float duration);
};

#endif CONTACT_RIGIDBODY_RESOLVER

