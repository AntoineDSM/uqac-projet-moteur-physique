//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

#include "ParticleDrag.h"
#include "Vector3D.h"
#include "Particle.h"

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

	//On r�cup�re son acc�l�ration
	Vector3D acceleration;
	velocity = particle->getAcceleration();

	//On calcule notre force de train�e relative aux coefficient relatifs
	Vector3D dragCoeff;
	double arg1 = velocity.get_magnitude() * m_k1;
	double arg2 = acceleration.get_magnitude() * m_k2;
	double sum = arg1 + arg2;
	dragCoeff = Vector3D::get_normalization(velocity) * sum;

	//On applique la force de train�e pendant la dur�e de la frame � notre vitesse. 
	particle->setVelocity((velocity - dragCoeff) * (double)duration);
}