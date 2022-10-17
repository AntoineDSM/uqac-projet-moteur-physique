<<<<<<< HEAD
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
		void resolveContacts (ParticleContact* contactArray[], unsigned int numContact, float duration);

=======
class ParticleContactResolver
{ 

protected:
// number of allowed iteration
unsigned int iteration;
public:
/ take an array of contact,
// Iterate on each contact according to their separatingVelocity
// Stop when all contacts are solved or when max iteration is reached
void resolveContacts (ParticleContact* contactArray,
unsigned int numContact, float duration);
>>>>>>> origin/Victor
};
