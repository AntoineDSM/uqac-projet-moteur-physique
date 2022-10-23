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
	*contact = ParticleContact(particle, restitution, maxLength);
}

float ParticleCable::currentLength() const
{
	return maxLength;
}