//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleSpring.h"
#include <math.h>

void ParticleSpring::updateForce(Particle* particle, float duration) {
	// Calcule le vecteur du ressort
	Vector3D force; 
	particle->getPosition(&force);

	//Je n'arrive pas � faire fonctionner 
	force-=m_other->getPosition();
    //force.operator-=(m_other->getPosition());

	// Calcule la magnitude de la force. 

	double magnitude = force.get_magnitude();
	magnitude = abs(magnitude - m_restlength);
	magnitude *= m_k;

	// Calcule la force finale et l'applique.

	force.get_normalization();
	force *= -magnitude;
	particle->addForce(force);
}