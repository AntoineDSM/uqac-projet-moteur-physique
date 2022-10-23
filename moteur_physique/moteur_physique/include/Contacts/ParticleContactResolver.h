#pragma once

#include "ParticleContact.h"
#include "ParticleCable.h"
#include "ParticleConctactGenerator.h"
#include "Particlelink.h"
#include "ParticleRod.h"
#include "WallContactGenerator.h"

class ParticleContactResolver
{ 

	protected:
		
		//Nombre d'iterations autorisées
		unsigned int iteration;
	
	public:

		ParticleContactResolver(int iteration) : iteration(iteration)
		{
			//rien a ajouter
		}
		
		//Prend un array de contacts,
		//Itere sur chaque contact par rapport à leur separatingVelocity
		//s'arrete lorsque tous les contacts ont été résolu ou que le nombre max d'itérations est atteind.
		void resolveContacts (std::vector<ParticleContact*> listeContacts);

		void resolveSpecialsContacts(std::vector<ParticleContact*> listeContacts = std::vector<ParticleContact*>());

};
