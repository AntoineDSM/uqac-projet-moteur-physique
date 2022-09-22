
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

#include "ParticleAnchoredSpring.h"


#include "ParticleBuoyancy.h"


void ParticleBuoyancy::updateForce(Particle* particle, float duration) {

	// Calcule la profondeur de submersion.

	double depth = particle->getPosition().y;

	// Vérifie si on est hors de l'eau. 

	if (depth >= m_waterHeight + m_maxDepth) return; Vector3D force(0, 0, 0);

	// Vérifier si nous sommes à la profondeur maximale.  

	if (depth <= m_waterHeight - m_maxDepth) {
	}

	force.y = m_liquidDensity * m_volume;

	particle->addForce(force);
	return;



	// Sinon, nous sommes partiellement submergés.

	force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth; particle->addForce(force);
}