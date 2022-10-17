<<<<<<< HEAD
#pragma once

#include "Particlelink.h"
#include "ParticleContact.h"

class ParticleCable: public ParticleLink
{
	public:

		//un contact sera généré entre deux particules si la distance les séparant est inférieure à cette variable.
		float maxLength;

		//Rempli un ParticleContact en fonction des informations de particles et de contact générator.
		unsigned int addContact (ParticleContact* contact, unsigned int limit) const;

};
=======
class ParticleCable: public ParticleLink
{
public:
// a contact will be generated if the distance
// between particles is larger than maxlength.
float maxLength;
// bounciness of the cable float restitution;
// Fill ParticleContact with information from particles and contact generator
unsigned int addContact (ParticleContact* contact, unsigned int limit) const;};
>>>>>>> origin/Victor
