#pragma once

//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD
#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"
using namespace moteurJeux;

// spring fixed to a position
class ParticleAnchoredSpring : public ParticleForceGenerator {
private:

	// other anchor

	Vector3D m_anchor;

	// drag coefficients
	float m_k;

	// length of the string in rest position
	float m_restLength;

public:
	// apply Hooke's law based on particles position
	void UpdateForce(Particle* particle, float duration);
};

