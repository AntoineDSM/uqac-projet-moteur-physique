#pragma once

#include "ParticleContact.h"

class ParticleContactResolver
{

protected:

	//Nombre d'iterations autorisées
	unsigned int iteration;

public:

	//Prend un array de contacts,
	//Itere sur chaque contact par rapport à leur separatingVelocity
	//s'arrete lorsque tous les contacts ont été résolu ou que le nombre max d'itérations est atteind.
	void resolveContacts(ParticleContact* contactArray[], unsigned int numContact, float duration);

};