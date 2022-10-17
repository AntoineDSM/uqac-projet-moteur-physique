#pragma once

#include "ParticleContact.h"

class ParticleContactResolver
{

protected:

	//Nombre d'iterations autoris�es
	unsigned int iteration;

public:

	//Prend un array de contacts,
	//Itere sur chaque contact par rapport � leur separatingVelocity
	//s'arrete lorsque tous les contacts ont �t� r�solu ou que le nombre max d'it�rations est atteind.
	void resolveContacts(ParticleContact* contactArray[], unsigned int numContact, float duration);

};