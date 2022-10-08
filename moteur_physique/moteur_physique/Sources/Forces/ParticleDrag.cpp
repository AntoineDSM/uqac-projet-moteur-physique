//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

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

	//On récupère son accélération
	Vector3D acceleration;
	velocity = particle->getAcceleration();
	
	//On calcule notre force de trainée relative aux coefficient relatifs
	Vector3D dragCoeff;
	double arg1 = velocity.get_magnitude() * m_k1;
	double arg2 = acceleration.get_magnitude() * m_k2;
	double sum = arg1 + arg2;
	dragCoeff = Vector3D::get_normalization(velocity) * sum;

	//On applique la force de trainée pendant la durée de la frame à notre vitesse. 
	particle->setVelocity((velocity - dragCoeff) * duration);
} 
