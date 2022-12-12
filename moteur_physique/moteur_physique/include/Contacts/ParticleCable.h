#pragma once

#ifndef PARTICLE_CABLE
#define PARTICLE_CABLE

#include "Particlelink.h"
#include "ParticleContact.h"

class ParticleCable: public ParticleLink
{
	public:

		//un contact sera g�n�r� entre deux particules si la distance les s�parant est sup�rieure � cette variable.
		float maxLength;

		float restitution;

		ParticleCable(Particle* particles[2], float maxLength, float restitution);

		//Retourne la longueur du lien
		float currentLength() const;

		//Rempli un ParticleContact en fonction des informations de particles et de contact g�n�rator.
		void addContact(ParticleContact* contact);

};

#endif PARTICLE_CABLE
