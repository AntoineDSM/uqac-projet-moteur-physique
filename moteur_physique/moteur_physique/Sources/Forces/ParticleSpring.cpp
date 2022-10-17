//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

#include "Forces/ParticleSpring.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"
#include <math.h>

using namespace moteurJeux;

<<<<<<< HEAD
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
	

=======
void ParticleSpring::updateForce(Particle* particle, float duration) {
	
	/*
	// Calcule le vecteur du ressort
	Vector3D force; 
	particle->getPosition(&force);

	//Je n'arrive pas à faire fonctionner 
	force-=m_other->getPosition();
    //force.operator-=(m_other->getPosition());

	// Calcule la magnitude de la force. 

	double magnitude = force.get_magnitude();
	magnitude = abs(magnitude - m_restlength);
	magnitude *= m_k;

	// Calcule la force finale et l'applique.

	force.get_normalization();
	force *= -magnitude;
	particle->addForce(force);

	*/
>>>>>>> origin/Victor
}