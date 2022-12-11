#pragma once

#ifndef PARTICLE_FORCE_GENERATOR
#define PARTICLE_FORCE_GENERATOR

#include "Particles/Particle.h"

// On peut demander � un g�n�rateur de force d'ajouter une force � une ou plusieurs particules. La foncton update force permet d'effectuer cette action.
class ParticleForceGenerator {

	public:
		
		// Surcharge cette fonction dans les impl�mentations de l'interface pour calculer et mettre � jour la force appliqu�e � la particule donn�e. 
		virtual void updateForce(Particle* particle, float duration) = 0;
};

#endif PARTICLE_FORCE_GENERATOR


