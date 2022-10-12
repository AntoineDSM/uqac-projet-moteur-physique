
#include "ParticleContact.h"


class ParticleContactResolver : public ParticleContact
{

protected:
	// number of allowed 
	unsigned int iteration;
public:
	// take an array of contact,
	// Iterate on each contact according to their separatingVelocity
	// Stop when all contacts are solved or when max iteration is reached
	void resolveContacts(ParticleContact* contactArray, unsigned int numContact, float duration);
};
