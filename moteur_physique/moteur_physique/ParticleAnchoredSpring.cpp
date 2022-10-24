
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleAnchoredSpring.h"


void ParticleAnchoredSpring::updateForce(Particle* particle, float duration) {
	
	// Calculate the vector of the spring. 
	
	Vector3D force; 
	
	particle->getPosition(&force); 
	
	force -= m_anchor;