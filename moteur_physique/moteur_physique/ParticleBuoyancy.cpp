
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

#include "ParticleAnchoredSpring.h"


#include "ParticleBuoyancy.h"


void ParticleBuoyancy::updateForce(Particle* particle, float duration) {

	// Calculate the submersion depth.

	double depth = particle->getPosition().y;

	// Check if we’re out of the water. 

	if (depth >= m_waterHeight + m_maxDepth) return; Vector3D force(0, 0, 0);

	// Check if we’re at maximum depth. 

	if (depth <= m_waterHeight - m_maxDepth) {
	}

	force.y = m_liquidDensity * m_volume;

	particle->addForce(force);
	return;



	// Otherwise we are partly submerged. 

	force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth; particle->addForce(force);
}