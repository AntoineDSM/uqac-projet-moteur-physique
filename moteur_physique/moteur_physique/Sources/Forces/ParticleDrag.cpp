//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

#include "Forces/ParticleDrag.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"

using namespace moteurJeux;

void ParticleDrag::updateForce(Particle* particle, float duration) {

	/*
	Vector3D force; particle->getVelocity(&force); 
	// Calculer le coefficient de traînée total  
	double dragCoeff = force.get_magnitude(); 
	
	dragCoeff = m_k1 * dragCoeff + m_k2 * dragCoeff * dragCoeff; 

	// Calcule la force finale et l'applique. 

	force.get_normalization();

	force *= -dragCoeff;

	particle->addForce(force);
	*/
} 
