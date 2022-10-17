//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification 21/09/22
//Modifié par : Victor GUIRAUD


#include "Forces/ParticleGravity.h"
#include "Particles/Particle.h"
#include "Vector3D/Vector3D.h"
	
using namespace moteurJeux
;

<<<<<<< HEAD
//Constructeur
ParticleGravity::ParticleGravity(const Vector3D& gravity) : gravity(gravity)
{
	//rien a faire ici.
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
	particle->setVelocity((velocity+adaptedGravity)*duration);
=======
ParticleGravity::ParticleGravity(const Vector3D& gravity)
	: gravity(gravity)
{
}
void ParticleGravity::updateForce(Particle* particle, float duration) {

	/*

	// Vérifier que nous n'avons pas une masse infinie.
	if (!particle->hasFiniteMass()) return;


	// Appliquer la force à l'échelle de la masse à la particule.
	
	// le code multiplie un vecteur et un scalaire je n'arrive pas à le faire fonctionner
	particle->addForce(gravity*particle->getMass());
	//particle->addForce(gravity.operator*=(particle->getMass()));
	*/
>>>>>>> origin/Victor
}