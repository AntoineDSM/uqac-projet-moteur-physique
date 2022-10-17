
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#pragma once

#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;
<<<<<<< HEAD
class ParticleBuoyancy : ParticleForceGenerator
{

	protected : 
		// propriétés des particules
		float m_maxDepth;
		float m_volume;
	
		// propriétés des effets
		float m_waterHeight;
		float m_liquidDensity;
	
	public:
		
		// Créer une nouvelle force de flottabilité avec les paramètres donnés. 
		ParticleBuoyancy(float m_maxDepth, float m_volume, float m_waterWeight, float m_liquidDensity = 1000.f);
		
		//Applique de la flottabilité basée sur la position de la particule
		void updateForce(Particle* particle, float duration);
=======
class ParticleBuoyancy
{
	// propriétés des particules
	float m_maxDepth;
	float m_volume;

	// propriétés des effets
	float m_waterHeight;
	float m_liquidDensity;

public:
	
	// Créer une nouvelle force de flottabilité avec les paramètres donnés. 
	ParticleBuoyancy(float m_maxDepth, float m_volume, float m_waterWeight, float m_liquidDensity = 1000.f);
	
	//Applique de la flottabilité basée sur la position de la particule
	void updateForce(Particle* particle, float duration);
>>>>>>> origin/Victor
};

