
#include "ParticleContactGenerator.h"


class ParticleLink : public ParticleContactGenerator
{
public:
	// Linked particles
	Particle* particle[2];
	// return the length of the link
	float currentLength() const;
	// Take a pointer to an array of contact and the number of contact left to be generated
	unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;
};
