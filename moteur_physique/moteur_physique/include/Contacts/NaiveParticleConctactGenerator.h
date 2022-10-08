#include "Contacts/ParticleConctactGenerator.h"
#include <stdlib.h>
#include <vector>
#include "Particles/Particle.h"
#include "Contacts/ParticleContact.h"


class NaiveParticleContactGenerator : public ParticleContactGenerator
{
	// Particle radius
	float radius;
	// particles that could collide together 
	std::vector<Particle*> particles;
	// iterate through every pair of particles to check their penetration
	unsigned int addContact (ParticleContact* contact, unsigned int limit) const;
};
