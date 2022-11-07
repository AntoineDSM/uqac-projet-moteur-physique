#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* particles[2], float length) : length(length)
{
	particle[0] = particles[0];
	particle[1] = particles[1];
}

void ParticleRod::addContact(ParticleContact* contact)
{
	*contact = ParticleContact(particle, 1, length);
}

float ParticleRod::currentLength() const
{
	return length;
}