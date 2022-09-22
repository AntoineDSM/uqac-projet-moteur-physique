//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleDrag.h"
#include "Vector3D.h"
#include "Particle.h"

using namespace moteurJeux;

void ParticleDrag::updateForce(Particle* particle, float duration) {

	Vector3D force; particle->getVelocity(&force); 
	// Calculate the total drag coefficient. 
	double dragCoeff = force.get_magnitude(); 
	
	dragCoeff = m_k1 * dragCoeff + m_k2 * dragCoeff * dragCoeff; 

	// Calculate the final force and apply it. 

	force.get_normalization();

	force *= -dragCoeff;

	particle->addForce(force);
} 
