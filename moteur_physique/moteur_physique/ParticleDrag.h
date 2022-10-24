
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD

#pragma once
#include "Vector3D.h"
#include "ParticleForceGenerator.h"

using namespace moteurJeux;
class ParticleDrag : public ParticleForceGenerator
{
private :
	//Coefficients de tra�n�e
	float m_k1;
	float m_k2;

public:

	// Cr�e le g�n�rateur avec les coefficients donn�s. 
		
		ParticleDrag(float m_k1, float m_k2);

    // Applique une tra�n�e simplifi�e bas�e sur la v�locit� de la particule
	void updateForce(Particle* particle, float duration);
};

