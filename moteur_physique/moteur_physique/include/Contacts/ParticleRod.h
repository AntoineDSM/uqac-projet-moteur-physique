#pragma once

#ifndef PARTICLE_ROD
#define PARTICLE_ROD

#include "Particlelink.h"
#include "ParticleContact.h"

class ParticleRod: public ParticleLink
{

	public:
		
		// un contact sera genereux si la distance / entre les particules n'est pas �gale � la longueur.
		float length;

		ParticleRod(Particle* particles[2], float length);

		//Retourne la longueur du lien
		float currentLength() const;

		// Remplir ParticleContact avec les informations des particules et du g�n�rateur de contact.
		// Le contact est diff�rent si la distance est plus courte ou plus grande que la longueur.
		void addContact(ParticleContact* contact);

};

#endif PARTICLE_ROD
