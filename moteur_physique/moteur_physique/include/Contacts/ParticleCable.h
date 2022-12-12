#pragma once

#ifndef PARTICLE_CABLE
#define PARTICLE_CABLE

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

#endif PARTICLE_CABLE
