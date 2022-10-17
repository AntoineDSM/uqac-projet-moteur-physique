<<<<<<< HEAD
#pragma once

#include "ParticleConctactGenerator.h"


class ParticleLink : public ParticleContactGenerator
{ 

	public:
		
		//Particules associées
		Particle* particle [2];

		//Retourne la longueur du lien
		float currentLength() const;

		//Prend un pointeur vers un array de contact et le nombre de contact restant a generer.
		unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;

};
=======
class ParticleLink : public ParticleContactGenerator
{ public:
// Linked particles
Particle* particle [2];
// return the length of the link
float currentLength() const;
// Take a pointer to an array of contact and the number of contact left to be generated
unsigned int addContact(ParticleContact* contact, unsigned int limit) const = 0;};
>>>>>>> origin/Victor
