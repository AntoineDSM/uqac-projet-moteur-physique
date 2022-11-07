#include "Forces/ParticleGravity.h"
#include "Particles/Particle.h"
#include "Vector3D/Vector3D.h"
#include "..\ValuesReferences.h"
	
using namespace moteurJeux;
using namespace valuesReferences;

//Constructeur
ParticleGravity::ParticleGravity(Vector3D& gravity) : gravity(gravity)
{
	gravityValue = gravity;
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
	velocity.addScaledVector(gravity, duration);
	particle->setVelocity(velocity);
}