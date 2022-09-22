
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD

#pragma once
#include "Vector3D.h"
#include "ParticleForceGenerator.h"

using namespace moteurJeux;
class ParticleDrag : public ParticleForceGenerator
{
private :
	//Coefficients de traînée
	float m_k1;
	float m_k2;

public:

	// Crée le générateur avec les coefficients donnés. 
		
		ParticleDrag(float m_k1, float m_k2);

    // Applique une traînée simplifiée basée sur la vélocité de la particule
	void updateForce(Particle* particle, float duration);
};

