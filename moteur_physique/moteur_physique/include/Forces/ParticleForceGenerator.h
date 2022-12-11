#pragma once

#ifndef PARTICLE_FORCE_GENERATOR
#define PARTICLE_FORCE_GENERATOR

#include "Particles/Particle.h"

// On peut demander à un générateur de force d'ajouter une force à une ou plusieurs particules. La foncton update force permet d'effectuer cette action.
class ParticleForceGenerator {

	public:
		
		// Surcharge cette fonction dans les implémentations de l'interface pour calculer et mettre à jour la force appliquée à la particule donnée. 
		virtual void updateForce(Particle* particle, float duration) = 0;
};

#endif PARTICLE_FORCE_GENERATOR


