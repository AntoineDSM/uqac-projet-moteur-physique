
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#pragma once

#include "ParticleForceGenerator.h"

using namespace moteurJeux;
class ParticleBuoyancy
{
	//particle properties
	float m_maxDepth;
	float m_volume;

	//effect properties
	float m_waterHeight;
	float m_liquidDensity;

public:
	
	/** Creates a new buoyancy force with the given parameters. */
	ParticleBuoyancy(float m_maxDepth, float m_volume, float m_waterWeight, float m_liquidDensity = 1000.f);
	//apply Buoyancy based on particle position
	void updateForce(Particle* particle, float duration);
};

