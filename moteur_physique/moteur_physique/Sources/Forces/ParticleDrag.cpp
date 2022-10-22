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
	//On récupère la vitesse de notre particle
	Vector3D velocity; 
	velocity = particle->getVelocity(); 

	
	//On calcule notre force de trainée relative aux coefficient relatifs
	Vector3D dragCoeff;
	Vector3D powVelocity = (velocity * velocity);
	Vector3D arg1 = moteurJeux::Vector3D::get_abs(velocity) * m_k1;
	Vector3D arg2 = moteurJeux::Vector3D::get_abs(powVelocity) * m_k2;
	Vector3D sum = arg1 + arg2;
	dragCoeff = Vector3D::get_normalization(sum);

	//On applique la force de trainée pendant la durée de la frame à notre vitesse. 
	velocity.addScaledVector(dragCoeff  * (float)(-1), duration);
	particle->setVelocity(velocity);
} 
