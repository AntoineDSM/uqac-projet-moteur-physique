//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleSpring.h"
#include <math.h>

void ParticleSpring::updateForce(Particle* particle, float duration) {
	// Calculate the vector of the spring. 
	Vector3D force; 
	particle->getPosition(&force); 
    force -= m_other->getPosition();

	// Calculate the magnitude of the force. 

	double magnitude = force.get_magnitude();
	magnitude = abs(magnitude - m_restlength);
	magnitude *= m_k;

	// Calculate the final force and apply it. 

	force.get_normalization();
	force *= -magnitude;
	particle->addForce(force);
}