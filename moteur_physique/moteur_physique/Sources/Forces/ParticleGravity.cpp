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

//implémentation de updateForce() de l'interface ParticleForceGenerator permettant d'appliquer la force de gravité à notre objet. 
void ParticleGravity::updateForce(Particle* particle, float duration)
{
	// Appliquer la force à l'échelle de la masse à la particule.

	//On cast la gravité dans un vector3D non const
	Vector3D adaptedGravity = gravity;
	adaptedGravity *= particle->getMass();

	//On cast la vitesse dans un vecteur3D non const
	Vector3D velocity = particle->getVelocity();

	//On applique la force de gravité pendant la durée de la frame à notre vitesse. 
	velocity.addScaledVector(gravity, duration);
	particle->setVelocity(velocity);
}