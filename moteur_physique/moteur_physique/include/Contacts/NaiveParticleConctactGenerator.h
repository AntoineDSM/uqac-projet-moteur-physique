#include "Contacts/ParticleContactGenerator.h"
#include <stdlib.h>
#include <vector>
#include "Particles/Particle.h"
#include "Contacts/ParticleContact.h"


class NaiveParticleContactGenerator : public ParticleContactGenerator
{
<<<<<<< HEAD

	public :
		
		//Rayon de la particule
		float radius;
		
		//Particules qui peuvent avoir des collisions
		std::vector<Particle*> particles;
		
		//Iteration a travers toutes les paires de particules pour verifier l'�tat de la p�n�tration.
		unsigned int addContact(ParticleContact* contact, unsigned int limit) const;

=======
	// Particle radius
	float radius;
	// particles that could collide together 
	std::vector<Particle*> particles;
	// iterate through every pair of particles to check their penetration
	unsigned int addContact (ParticleContact* contact, unsigned int limit) const;
>>>>>>> origin/Victor
};
