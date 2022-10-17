
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 21/09/22
//Modifi� par : Victor GUIRAUD

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