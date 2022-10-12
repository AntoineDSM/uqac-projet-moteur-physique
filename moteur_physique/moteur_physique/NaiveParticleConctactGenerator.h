#include "ParticleContactGenerator.h"
#include "Particle.h"
#include <vector>
#include <iostream>




class NaiveParticleContactGenerator : public ParticleContactGenerator
{
	// Particle radius
	float radius;
	// particles that could collide together 
	std::vector<Particle*> particles;
	// iterate through every pair of particles to check their penetration
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const;
};
