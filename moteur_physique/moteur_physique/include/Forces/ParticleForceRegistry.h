#pragma once

#ifndef PARTICLE_FORCE_REGISTRY
#define PARTICLE_FORCE_REGISTRY

#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"
#include "Forces/ParticleForceGenerator.h"
#include "Forces/ParticleBuoyancy.h"
#include "Forces/ParticleDrag.h"
#include "Forces/ParticleForceGenerator.h"
#include "Forces/ParticleGravity.h"
#include "Forces/ParticleSpring.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace moteurJeux;


//Applique des forces à toutes les particules qui sont liées à ces forces.
// Détient tous les générateurs de force et les particules auxquelles ils s'appliquent.
class ParticleForceRegistry
{

	protected:
		
		// Garde la trace d'un générateur de force et de la particule à laquelle il s'applique.
		struct ParticleForceRegistration {
			Particle* particle;
			ParticleForceGenerator* forceGenerator;
		}; 
	
		//Détient la liste des enregistrements
		using Registry = std::vector<ParticleForceRegistration> ;
		
		Registry registrations; 
	
	public: 
	
		// Enregistre le générateur de force donné à appliquer à la particule donnée.
		void add(Particle* particle, ParticleForceGenerator* forceGenerator); 
		
		// Supprime la paire enregistrée donnée du registre. Si la paire n'est pas enregistrée, cette méthode n'aura aucun effet.
		void remove(Particle* particle, ParticleForceGenerator* forceGenerator); 
		
		//Efface tous les enregistrements du registre, seulement les enregistrements de leur connexion sont supprimés.
	    void clear();
	
		//Appelle tous les générateurs de force pour mettre à jour les forces de leurs particules correspondantes.
		void updateForces(float duration);
}; 


#endif PARTICLE_FORCE_REGISTRY



