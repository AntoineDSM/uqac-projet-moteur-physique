
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD

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

