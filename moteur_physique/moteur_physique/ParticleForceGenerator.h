
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD




#include "Particle.h"

#pragma once

#ifndef PARTICLEFORCEGENERATOR_HPP
#define PARTICLEFORCEGENERATOR_HPP


// On peut demander � un g�n�rateur de force d'ajouter une force � une ou plusieurs particules.

class ParticleForceGenerator {

public:
	// Surcharge cette fonction dans les impl�mentations de l'interface pour calculer et mettre � jour la force appliqu�e � la particule donn�e. 
	virtual void updateForce(Particle* particle, float duration) = 0;
};
#endif PARTICLECONTACT_HPP