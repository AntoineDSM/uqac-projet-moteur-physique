#include "Forces/ParticleDrag.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"

using namespace moteurJeux;

ParticleDrag::ParticleDrag(double m_k1, double m_k2) : m_k1(m_k1), m_k2(m_k2)
{
	//rien de plus a faire ici.
}

void ParticleDrag::updateForce(Particle* particle, float duration) 
{
	//On r�cup�re la vitesse de notre particle
	Vector3D velocity; 
	velocity = particle->getVelocity(); 

	
	//On calcule notre force de train�e relative aux coefficient relatifs
	Vector3D dragCoeff;
	Vector3D powVelocity = (velocity * velocity);
	Vector3D arg1 = velocity * m_k1;
	Vector3D arg2 = powVelocity * m_k2;
	Vector3D sum = arg1 + arg2;
	dragCoeff = Vector3D::get_normalization(sum);

	//On applique la force de train�e pendant la dur�e de la frame � notre vitesse. 
	velocity.addScaledVector(dragCoeff  * (float)(-1), duration);
	particle->setVelocity(velocity);
} 

/*void ParticleDrag::updateForce(Particle* particle, real duration) { Vector3 force; particle->getVelocity(&force); // Calculate the total drag coefficient. real dragCoeff = force.magnitude(); dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff; } // Calculate the final force and apply it. force.normalize(); force *= -dragCoeff; particle->addForce(force);*/