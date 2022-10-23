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
	if (d.x != 0)
	{
		d.x -= m_restlength;
	}
	if (d.y != 0)
	{
		d.y -= m_restlength;
	}
	if (d.z != 0)
	{
		d.z -= m_restlength;
	}
	force = Vector3D::get_normalization_2(d * m_k * (float)(-1));

	velocity_1.addScaledVector(force , duration);
	velocity_2.addScaledVector(force * (float)(-1), duration);
	particle->setVelocity(velocity_1);
	m_other->setVelocity(velocity_2);
	

}