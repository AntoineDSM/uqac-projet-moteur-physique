<<<<<<< HEAD
#pragma once

#include "Particlelink.h"
#include "ParticleContact.h"

class ParticleCable: public ParticleLink
{
	public:

		//un contact sera généré entre deux particules si la distance les séparant est supérieure à cette variable.
		float maxLength;

		float restitution;

		ParticleCable(Particle* particles[2], float maxLength, float restitution);

		//Retourne la longueur du lien
		float currentLength() const;

		//Rempli un ParticleContact en fonction des informations de particles et de contact générator.
		void addContact(ParticleContact* contact);

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
