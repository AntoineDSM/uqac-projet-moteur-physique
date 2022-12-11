#pragma once

#ifndef PARTICLE_SPRING
#define PARTICLE_SPRING

#include "Vector3D/Vector3D.h"
#include "Forces/ParticleForceGenerator.h"
#include "../../ParticleForceGenerator.h"

using namespace moteurJeux;

//Ressort entre deux particules
class ParticleSpring : public ParticleForceGenerator
{
	protected:
	
		//autre ancrage
		Particle* m_other;
	
		//constante du resort
		float m_k;
	
		//longueur au repos du ressort
		float m_restlength;
	
	public:
	
		// Cr�e un nouveau ressort avec les param�tres donn�s.
		ParticleSpring(Particle* other, float m_k, float m_restLength);
	
		//Applique la loi de Hook bas�e sur la position de la particule
		void updateForce(Particle* particle, float duration);
};

#endif PARTICLE_SPRING
