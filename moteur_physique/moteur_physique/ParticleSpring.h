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
private:
	//other anchor
	Particle* m_other;
	//spring constant
	float m_k;


	float m_restlength;

public:

	//apply Hook's law based on particle position
	void updateForce(Particle* particle, float duration);
};

