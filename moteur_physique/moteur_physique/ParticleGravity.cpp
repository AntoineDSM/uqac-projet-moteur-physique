//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification 21/09/22
//Modifi� par : Victor GUIRAUD


#include "ParticleGravity.h"
#include "Particle.h"
#include "Vector3D.h"
	
using namespace moteurJeux
;

ParticleGravity::ParticleGravity(const Vector3D& gravity)
	: gravity(gravity)
{
}
void ParticleGravity::updateForce(Particle* particle, float duration) {


	// V�rifier que nous n'avons pas une masse infinie.
	if (!particle->hasFiniteMass()) return;


	// Appliquer la force � l'�chelle de la masse � la particule.
	
	// le code multiplie un vecteur et un scalaire je n'arrive pas � le faire fonctionner
	particle->addForce(gravity*particle->getMass());
	//particle->addForce(gravity.operator*=(particle->getMass()));
}