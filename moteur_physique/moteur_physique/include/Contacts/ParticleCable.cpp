#include "ParticleCable.h"
#include "ParticleContact.h"
#include <Contacts/NaiveParticleConctactGenerator.h>

ParticleCable::ParticleCable(Particle* particles[2], float maxLength, float restitution) : maxLength(maxLength), restitution(restitution)
{
	particle[0] = particles[0];
	particle[1] = particles[1];
}

void ParticleCable::addContact(ParticleContact* contact)
{
	float distance = std::sqrt((Precision::carre(particle[1]->getPosition().x - particle[0]->getPosition().x)) + (Precision::carre(particle[1]->getPosition().y - particle[0]->getPosition().y)) + (Precision::carre(particle[1]->getPosition().z - particle[0]->getPosition().z)));
	if (distance > maxLength)
	{
		*contact = ParticleContact(particle, restitution, 0);
	}
}

float ParticleCable::currentLength() const
{
	return maxLength;
}