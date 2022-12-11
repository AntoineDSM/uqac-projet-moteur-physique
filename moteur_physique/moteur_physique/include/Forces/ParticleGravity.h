#pragma once

#ifndef PARTICLE_GRAVITY
#define PARTICLE_GRAVITY

#include "Vector3D/Vector3D.h"
#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;

//forces gravitationnels 
class ParticleGravity : public ParticleForceGenerator
{

	public :

		Vector3D gravity;

	public:

		// Cr�e le g�n�rateur avec l'acc�l�ration donn�e. 
		ParticleGravity(Vector3D& gravity);

		//Applique la force de gravit� en fonction de la masse de particle adapt� en fonction de la dur�e de la frame.
		void updateForce(Particle* particle, float duration);

};

#endif PARTICLE_GRAVITY
