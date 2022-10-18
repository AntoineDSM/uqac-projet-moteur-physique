//Date de création :
//Créer par : 
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#pragma once

#include "math.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"
#include "Utils/Precision.h"

#ifndef PARTICLECONTACT_HPP
#define PARTICLECONTACT_HPP

class ParticleContact{
  
	public:

		// Particle[0] => Particle A
		// Particle[0] => Particle B - could be nullptr
		Particle* particle[2];
		
		//valeur entre 0 et 1 qui définie l'elasticité de la collision.
		float restitution;
		
		//distance de pénétration du contact.
		float penetration;
		
		//Vecteur normal aux particles.
		Vector3D contactNormal;

		ParticleContact(Particle* particle[2], float restitution, float penetration, Vector3D contactNormal);

		//Resoud la vitesse et l'interpenetration de nos particles.
		void resolve (float duration);
		
		//retourne la différence de vitesse entre nos particles.
		float calculatingSeparatingVelocity();
		
		//Resoud l'impulsion générée.
		void resolveVelocity(float e = 1);
		
		//Resoud l'interpénétration entre nos particles.
		void resolveInterpretation();

};

#endif PARTICLECONTACT_HPP
