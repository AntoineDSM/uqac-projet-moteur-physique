
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD

#pragma once

#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;
<<<<<<< HEAD
class ParticleBuoyancy : ParticleForceGenerator
{

	protected : 
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
=======
class ParticleBuoyancy
{
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
>>>>>>> origin/Victor
};

