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
		
		//Nombre d'iterations autoris�es
		unsigned int iteration;
	
	public:

		ParticleContactResolver(int iteration) : iteration(iteration)
		{
			//rien a ajouter
		}
		
		//Prend un array de contacts,
		//Itere sur chaque contact par rapport � leur separatingVelocity
		//s'arrete lorsque tous les contacts ont �t� r�solu ou que le nombre max d'it�rations est atteind.
		void resolveContacts (std::vector<ParticleContact*> listeContacts);

		void resolveSpecialsContacts(std::vector<ParticleContact*> listeContacts = std::vector<ParticleContact*>());

};
