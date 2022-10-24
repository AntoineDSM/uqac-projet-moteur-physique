
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleAnchoredSpring.h"


#include "ParticleBuoyancy.h"


void ParticleBuoyancy::updateForce(Particle* particle, float duration) {

	// Calcule la profondeur de submersion.

	double depth = particle->getPosition().y;

	// V�rifie si on est hors de l'eau. 

	if (depth >= m_waterHeight + m_maxDepth) return; Vector3D force(0, 0, 0);

	// V�rifier si nous sommes � la profondeur maximale.  

	if (depth <= m_waterHeight - m_maxDepth) {
	}

	force.y = m_liquidDensity * m_volume;

	particle->addForce(force);
	return;



	// Sinon, nous sommes partiellement submerg�s.

	force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth; particle->addForce(force);
}