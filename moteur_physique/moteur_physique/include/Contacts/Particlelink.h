#pragma once

#ifndef PARTICLE_LINK
#define PARTICLE_LINK

#include "Particles/particle.h"

class ParticleLink
{ 

	public:
		
		//Particules associ�es
		Particle* particle[2];


		ParticleLink()
		{
			//rien a ajouter
		};
};

#endif PARTICLE_LINK
