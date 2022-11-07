#include "Forces/ParticleBuoyancy.h"


ParticleBuoyancy::ParticleBuoyancy(float m_maxDepth, float m_volume, float m_waterheight, float m_liquidDensity) : m_maxDepth(m_maxDepth), m_volume(m_volume), m_waterHeight(m_waterheight), m_liquidDensity(m_liquidDensity)
{
	//Rien a ajouter ici
}

void ParticleBuoyancy::updateForce(Particle* particle, float duration)
{
	//On initialise notre vecteur force.
	Vector3D force(0, 0, 0);

	//On cast la vitesse dans un vecteur3D non const
	Vector3D velocity = particle->getVelocity();

	// Calcule la profondeur de submersion.
	double depth = particle->getPosition().y;

	// V�rifie si on est hors de l'eau. 
	if (depth >= m_waterHeight + m_maxDepth)
	{
		return;
	}

	// V�rifier si nous sommes � la profondeur maximale. L'object est compl�tement submerg�.
	if (depth <= m_waterHeight - m_maxDepth) 
	{
		force.y = m_liquidDensity * m_volume;//densit� du liquide par le volume de l'objet.
		velocity.addScaledVector(force, duration);
		particle->setVelocity(velocity);
		return;
	}

	// Sinon, nous sommes partiellement submerg�s.
	force.y = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / 2 * m_maxDepth;
	velocity.addScaledVector(force, duration);
	particle->setVelocity(velocity);
}