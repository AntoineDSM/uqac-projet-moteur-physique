//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification 21/09/22
//Modifié par : Victor GUIRAUD


#include "ParticleGravity.h"
#include "Particle.h"
#include "Vector3D.h"
	
using namespace moteurJeux
;

	
void ParticleGravity::updateForce(Particle* particle, float duration) {


	// Vérifier que nous n'avons pas une masse infinie.
	if (!particle->hasFiniteMass()) return;


	// Appliquer la force à l'échelle de la masse à la particule.
	// 
	// le code multiplie un vecteur et un scalaire je ne sais pas pourquoi
	particle->addForce(gravity * particle->getMass());
}