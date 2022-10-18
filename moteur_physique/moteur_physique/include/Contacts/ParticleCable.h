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
