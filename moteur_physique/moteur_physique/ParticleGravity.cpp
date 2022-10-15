//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification 21/09/22
//Modifi� par : Victor GUIRAUD


#include "Forces/ParticleGravity.h"
#include "Particles/Particle.h"
#include "Vector3D/Vector3D.h"

using namespace moteurJeux
;

//Constructeur
ParticleGravity::ParticleGravity(const Vector3D& gravity) : gravity(gravity)
{
	//rien a faire ici.
}

//impl�mentation de updateForce() de l'interface ParticleForceGenerator permettant d'appliquer la force de gravit� � notre objet. 
void ParticleGravity::updateForce(Particle* particle, float duration)
{
	// Appliquer la force � l'�chelle de la masse � la particule.

	//On cast la gravit� dans un vector3D non const
	Vector3D adaptedGravity = gravity;
	adaptedGravity *= particle->getMass();

	//On cast la vitesse dans un vecteur3D non const
	Vector3D velocity = particle->getVelocity();

	//On applique la force de gravit� pendant la dur�e de la frame � notre vitesse. 
	particle->setVelocity((velocity + adaptedGravity) * duration);
}