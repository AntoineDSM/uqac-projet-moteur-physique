#pragma once

#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;

class ParticleBuoyancy : public ParticleForceGenerator
{

	private : 
		// propri�t�s des particules
		float m_maxDepth;
		float m_volume;
	
		// propri�t�s des effets
		float m_waterHeight;
		float m_liquidDensity;
	
	public:
		
		// Cr�er une nouvelle force de flottabilit� avec les param�tres donn�s. 
		ParticleBuoyancy(float m_maxDepth, float m_volume, float m_waterWeight, float m_liquidDensity = 1000.f);
		
		//Applique de la flottabilit� bas�e sur la position de la particule
		void updateForce(Particle* particle, float duration);
};

