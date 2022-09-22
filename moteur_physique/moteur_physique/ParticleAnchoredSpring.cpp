
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

#include "ParticleAnchoredSpring.h"


void ParticleAnchoredSpring::updateForce(Particle* particle, float duration) {
	
	// Calculate the vector of the spring. 
	
	Vector3D force; 
	
	particle->getPosition(&force); 
	
	force -= m_anchor;