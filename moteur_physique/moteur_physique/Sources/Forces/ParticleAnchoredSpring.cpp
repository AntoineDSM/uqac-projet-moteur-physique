
//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 21/09/22
//Modifié par : Victor GUIRAUD

#include "Forces/ParticleAnchoredSpring.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"

using namespace moteurJeux;


void ParticleAnchoredSpring::updateForce(Particle* particle, float duration) {

	// Calcule le vecteur du ressort.

	Vector3D force;

	//particle->getPosition(&force); 

	force -= m_anchor;
}