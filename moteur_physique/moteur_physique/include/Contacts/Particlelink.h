#pragma once

#include "ParticleConctactGenerator.h"


class ParticleLink : public ParticleContactGenerator
{ 

	public:
		
		//Particules associ�es
		Particle* particle [2];

		//Retourne la longueur du lien
		float currentLength() const;

		//Prend un pointeur vers un array de contact et le nombre de contact restant a generer.
		unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

};
