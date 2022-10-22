#pragma once

#include "Particlelink.h"
#include "ParticleContact.h"

class ParticleRod: public ParticleLink
{

	public:
		
		// a contact will be genereated if the distance / between particles is not equal to the length.
		float length;

		ParticleRod(Particle* particles[2], float length);

		//Retourne la longueur du lien
		float currentLength() const;

		// Fill ParticleContact with information from particles and contact generator.
		// Contact is different wether the distance is shorter or greater then the length
		void addContact(ParticleContact* contact);

};
