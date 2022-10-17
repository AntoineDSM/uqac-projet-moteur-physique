#pragma once

//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD
#pragma once
#include "Particles/Particle.h"
#include "ParticleForceGenerator.h"
using namespace moteurJeux;

// ressort fix� � une position
class ParticleAnchoredSpring : public ParticleForceGenerator {
private:

	// other anchor

	Vector3D m_anchor;

	// autre ancre
	float m_k;

	// longueur de la cha�ne en position de repos
	float m_restLength;

public:

	// Cr�e un nouveau ressort avec les param�tres donn�s.
	ParticleAnchoredSpring(Vector3D* anchor, float m_k, float m_restLength);

	// Applique la loi de Hooke en fonction de la position des particules
	void updateForce(Particle* particle, float duration);
};

