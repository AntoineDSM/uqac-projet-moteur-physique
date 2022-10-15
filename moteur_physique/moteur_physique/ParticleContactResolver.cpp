#include <algorithm>

#include "ParticleContactResolver.h"
#include "Utils/Precision.h"

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray[], unsigned int numContact, float duration)
{
	//taille de notre liste de contacts
	const int size = sizeof(contactArray) / sizeof(contactArray[0]);
	//liste de tri des valeurs de vitesse relative entre nos particles
	int value[size];
	//liste des index rangés dans l'ordre croissant du contact le moins important au plus important
	int index[size];


	int cpt = 0;
	while (cpt < iteration)//tant que nous n'avons pas atteind le nombre max d'itération
	{
		if (size != 0)
		{
			for (int i = 0; i < size; i++)
			{
				value[i] = contactArray[i]->calculatingSeparatingVelocity();
				index[i] = i;
			}
		}

		Precision::sort(value, size, index);//on trie la liste des valeurs dans l'odre croissant et la liste des index est mise à jour en conséquence

		if (value[0] > 0)
		{
			std::cout << "tous les contacts sont résolus.\n";
			return;
		}
		else//on lance la résolution des contacts
		{
			for (int i = 0; i < size; i++)//parcours du contact le plus important au moins important
			{
				if (value[i] > 0)
				{
					//ne rien faire le contact est resolu
				}
				else
				{
					contactArray[index[i]]->resolve(duration);//on résoud le contact
				}
			}
		}
		cpt++;
	}
}
