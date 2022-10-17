#pragma once

//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD
#pragma once
#include "Particles/Particle.h"
#include "ParticleForceGenerator.h"
using namespace moteurJeux;

// ressort fixé à une position
class ParticleAnchoredSpring : public ParticleForceGenerator {
private:

	// other anchor

	Vector3D m_anchor;

	// autre ancre
	float m_k;

	// longueur de la chaîne en position de repos
	float m_restLength;

public:

	// Crée un nouveau ressort avec les paramètres donnés.
	ParticleAnchoredSpring(Vector3D* anchor, float m_k, float m_restLength);

	// Applique la loi de Hooke en fonction de la position des particules
	void updateForce(Particle* particle, float duration);
};

