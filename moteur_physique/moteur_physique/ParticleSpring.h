//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#pragma once
#include "Vector3D.h"
#include "ParticleForceGenerator.h"

using namespace moteurJeux;
//ressort entre deux particules
class ParticleSpring : public ParticleForceGenerator
{
protected:
	//autre ancrage
	Particle* m_other;

	//constante du resort
	float m_k;

	//longueur au repos du ressort
	float m_restlength;

public:
	// Crée un nouveau ressort avec les paramètres donnés.
	ParticleSpring(Particle* other, float m_k, float m_restLength);
	//Applique la loi de Hook basée sur la position de la particule
	void updateForce(Particle* particle, float duration);
};

