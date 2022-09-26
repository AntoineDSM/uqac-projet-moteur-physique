//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD

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
	// Cr�e un nouveau ressort avec les param�tres donn�s.
	ParticleSpring(Particle* other, float m_k, float m_restLength);
	//Applique la loi de Hook bas�e sur la position de la particule
	void updateForce(Particle* particle, float duration);
};

