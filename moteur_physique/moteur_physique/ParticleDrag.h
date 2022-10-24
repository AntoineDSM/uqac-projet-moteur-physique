
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
		//drag coefficients
	float m_k1;
	float m_k2;

public:

	/** Creates the generator with the given coefficients. */ 
		
		ParticleDrag(float m_k1, float m_k2);

	//apply simplified drag based on particle's velocity
	void updateForce(Particle* particle, float duration);
};

