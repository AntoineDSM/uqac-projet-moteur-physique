<<<<<<< HEAD
#pragma once

#include "ParticleContact.h"
#include "Particles/Particle.h"

class ParticleContactGenerator
{ 
	
	public:

		//Prend un pointeur vers un array de contact et le nombre de contact restant a generer.
		virtual unsigned int addContact (ParticleContact* contact, unsigned int limit) const = 0;

=======
class ParticleContactGenerator
{ public:

// Take a pointer to an array of contact and the number of contact left to be generated
virtual unsigned int addContact (ParticleContact* contact, unsigned int limit) const = 0;
>>>>>>> origin/Victor
};
