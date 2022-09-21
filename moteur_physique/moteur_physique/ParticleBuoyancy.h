
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
	float m_waterweight;
	float m_liquidensity;


	//apply Buoyancy based on particle position
	void updateForce(Particle* particle, float duration);
};

