//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#pragma once
#include "Vector3D.h"
#include "ParticleForceGenerator.h"

using namespace moteurJeux;
//spring between two particles
class ParticleSpring : public ParticleForceGenerator
{
protected:
	//other anchor
	Particle* m_other;

	//spring constant
	float m_k;

	//rest lenght of the spring
	float m_restlength;

public:
	/** Creates a new spring with the given parameters. */ 
	ParticleSpring(Particle* other, float m_k, float m_restLength);
	//apply Hook's law based on particle position
	void updateForce(Particle* particle, float duration);
};

