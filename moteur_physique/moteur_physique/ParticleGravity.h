
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD


#pragma once
#include "Vector3D.h"
#include "ParticleForceGenerator.h"

using namespace moteurJeux;

//gravitational forces
class ParticleGravity : public ParticleForceGenerator
{

protected :

	const Vector3D gravity;

public:

	/** Creates the generator with the given acceleration. */
	ParticleGravity(const Vector3D& gravity);

	// F= particle-> GetMass()*m_gravity
	void updateForce(Particle* particle, float duration);

};

