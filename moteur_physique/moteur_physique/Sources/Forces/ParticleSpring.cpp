#include "Forces/ParticleSpring.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"
#include <math.h>

using namespace moteurJeux;

ParticleSpring::ParticleSpring(Particle* other, float m_k, float m_restLength) : m_other(other), m_k(m_k), m_restlength(m_restLength)
{
	//Rien a ajouter ici.
}

void ParticleSpring::updateForce(Particle* particle, float duration)
{

	//On cast la vitesse dans un vecteur3D non const
	Vector3D velocity_1 = particle->getVelocity();
	Vector3D velocity_2 = m_other->getVelocity();

	//de même avec la position
	Vector3D position_1 = particle->getPosition();
	Vector3D position_2 = m_other->getPosition();
	
	//On initialise la force
	Vector3D force(0, 0, 0);

	//On initialise le delta position entre les deux
	Vector3D d = position_1 - position_2;
	force = Vector3D::get_normalization(d) * m_k * (d.get_magnitude() - m_restlength);

	//On applique
	particle->setVelocity((velocity_1 - force) * duration);
	m_other->setVelocity((velocity_2 - force) * duration);
	

}