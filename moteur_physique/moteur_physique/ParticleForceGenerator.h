
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD




#include "Particle.h"

#pragma once

#ifndef PARTICLEFORCEGENERATOR_HPP
#define PARTICLEFORCEGENERATOR_HPP


// On peut demander à un générateur de force d'ajouter une force à une ou plusieurs particules.

class ParticleForceGenerator {

public:
	// Surcharge cette fonction dans les implémentations de l'interface pour calculer et mettre à jour la force appliquée à la particule donnée. 
	virtual void updateForce(Particle* particle, float duration) = 0;
};
#endif PARTICLECONTACT_HPP