#include <algorithm>

#include "ParticleContactResolver.h"
#include "Utils/Precision.h"

void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*> listeContacts = std::vector<ParticleContact*>())
{
	if (listeContacts != std::vector<ParticleContact*>())
	{
		int size = static_cast<int>(listeContacts.size());
		//liste de tri des valeurs de vitesse relative entre nos particles
		std::vector<bool> value = std::vector<bool>();
		//liste des index rangés dans l'ordre croissant du contact le moins important au plus important
		//std::vector<int> index = std::vector<int>();

		
		int cpt = 0;
		while (cpt < iteration)//tant que nous n'avons pas atteind le nombre max d'itération, si la resolution d'un contact en créer d'autre
		{
			if (size > 0)
			{
				for (int i = 0; i < size; i++)
				{
					value.push_back(listeContacts[i]->separatingDistance());
					//index.push_back(i);
				}
			}

			for (int i = 0; i < size; i++)
			{
				if (value[i] == true)
				{
					listeContacts[i]->resolve();//on résoud le contact
				}
			}

			cpt++;
		}
	}
}

void ParticleContactResolver::resolveSpecialsContacts(std::vector<ParticleContact*> listeContacts)
{
	int size = static_cast<int>(listeContacts.size());
	if (listeContacts != std::vector<ParticleContact*>())
	{
		for (int i = 0; i < size; i++)
		{
			listeContacts[i]->resolve();//on résoud le contact		
		}
	}
}