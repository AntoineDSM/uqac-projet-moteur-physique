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

		// Crée le générateur avec l'accélération donnée. 
		ParticleGravity(Vector3D& gravity);

		//Applique la force de gravité en fonction de la masse de particle adapté en fonction de la durée de la frame.
		void updateForce(Particle* particle, float duration);

};

#endif PARTICLE_GRAVITY
