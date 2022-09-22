#pragma once

//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD
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

	/** Creates a new spring with the given parameters. */ 
	
	ParticleAnchoredSpring(Vector3D* anchor, float m_k, float m_restLength);
	// apply Hooke's law based on particles position
	void updateForce(Particle* particle, float duration);
};

