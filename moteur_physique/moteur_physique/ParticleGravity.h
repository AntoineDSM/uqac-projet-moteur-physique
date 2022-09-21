
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD


#pragma once
#include "Vector3D.h"
#include "ParticleForceGenerator.h"

using namespace moteurJeux;

//gravitational forces
class ParticleGravity : public ParticleForceGenerator
{

protected :

	Vector3D gravity;

public:

	// F= particle-> GetMass()*m_gravity
	void updateForce(Particle* particle, float duration);

};

