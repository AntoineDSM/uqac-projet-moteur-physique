#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* particles[2], float length) : length(length)
{
	particle[0] = particles[0];
	particle[1] = particles[1];
}

void ParticleRod::addContact(ParticleContact* contact)
{
	float distance = std::sqrt((Precision::carre(particle[1]->getPosition().x - particle[0]->getPosition().x)) + (Precision::carre(particle[1]->getPosition().y - particle[0]->getPosition().y)) + (Precision::carre(particle[1]->getPosition().z - particle[0]->getPosition().z)));
	if (distance > length)
	{
		*contact = ParticleContact(particle, 1, length);
	}
}

float ParticleRod::currentLength() const
{
	return length;
}