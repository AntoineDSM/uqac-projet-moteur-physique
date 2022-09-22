//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification 21/09/22
//Modifié par : Victor GUIRAUD


#include "ParticleGravity.h"
#include "Particle.h"
#include "Vector3D.h"
	
using namespace moteurJeux
;

	
void ParticleGravity::updateForce(Particle* particle, float duration) {


	// Check that we do not have infinite mass. 
	if (!particle->hasFiniteMass()) return;


	// Apply the mass-scaled force to the particle.
	// le code multiply un vecteur et un scalaire je ne sais pas pourquoi
	particle->addForce(gravity * particle->getMass());
}