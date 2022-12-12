#pragma once

#ifndef PARTICLE_DRAG
#define PARTICLE_DRAG

#include "Vector3D/Vector3D.h"
#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;

class ParticleDrag : public ParticleForceGenerator
{
	private :
	
		//Coefficients de traînée
		double m_k1;
		double m_k2;
	
	public:
	
		// Crée le générateur avec les coefficients donnés. 	
		ParticleDrag(double m_k1, double m_k2);
	
	    // Applique une traînée simplifiée basée sur la vélocité de la particule
		void updateForce(Particle* particle, float duration);
};

#endif PARTICLE_DRAG
