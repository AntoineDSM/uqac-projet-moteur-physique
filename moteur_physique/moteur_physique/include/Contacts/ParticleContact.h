#pragma once

#ifndef PARTICLECONTACT_HPP
#define PARTICLECONTACT_HPP

#include "math.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"
#include "Utils/Precision.h"
#include "../Headers/Wall.h"
#include <vector>

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

		ParticleContact(Particle* particle[2], float restitution = 0.8, float penetration = 0);

		//Resoud la vitesse et l'interpenetration de nos particles.
		void resolve ();
		
		//retourne la différence de vitesse entre nos particles.
		Vector3D calculatingSeparatingVelocity();
		
		//Resoud l'impulsion générée.
		void resolveVelocity();
		
		//Resoud l'interpénétration entre nos particles.
		bool resolveInterpretation();

		bool separatingDistance();

};

#endif PARTICLECONTACT_HPP
