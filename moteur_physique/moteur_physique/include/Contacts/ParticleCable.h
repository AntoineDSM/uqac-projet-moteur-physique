#pragma once

#include "Particlelink.h"
#include "ParticleContact.h"

class ParticleCable: public ParticleLink
{
	public:

		//un contact sera g�n�r� entre deux particules si la distance les s�parant est inf�rieure � cette variable.
		float maxLength;

		//Rempli un ParticleContact en fonction des informations de particles et de contact g�n�rator.
		unsigned int addContact (ParticleContact* contact, unsigned int limit) const;

};
