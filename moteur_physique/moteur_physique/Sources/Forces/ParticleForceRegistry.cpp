#include "Forces/ParticleForceRegistry.h"
#include "Vector3D/Vector3D.h"

using namespace moteurJeux; 

//Permet d'ajouter un registre de force, une force à appliquer à une particle à chaque tour de boucle
void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	//On créer notre registre
	ParticleForceRegistration newPFR;
	newPFR.particle = particle;
	newPFR.forceGenerator = forceGenerator;

	//On l'ajoute dans la liste les repertoriant
	registrations.push_back(newPFR);
}

//Permet de supprimer l'application d'une force à une particle
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* forceGenerator)
{
	bool exist = false;
	for(int i = 0; i < registrations.size(); i++)
	{
		ParticleForceRegistration PFR = registrations[i];
		if (PFR.particle == particle && PFR.forceGenerator == forceGenerator)
		{
			registrations.erase(registrations.begin() + i);
			exist = true;
		}
	}
	if (exist == true)
	{
		std::cout << "La force ne sera plus appliquée à la particule. \n";
	}
	else
	{
		std::cout << "La force n'était pas appliquée à cette particule. \n";
	}
}

//Permet de supprimer l'ensemble des forces enregistrées.
void ParticleForceRegistry::clear()
{
	if (registrations.size() != 0)
	{
		std::cout << "La liste des enregistrements est vide.\n";
	}
	else
	{
		for (int i = 0; i < registrations.size(); i++)
		{
			registrations.erase(registrations.begin() + i);
		}
		std::cout << "La liste des enregistrements a été vidée.\n";
	}
}

//Cette fonction sera appelée dans la boucle de jeu et permettra d'appliqué par le biais des registres de force, une force à une particle à  chaque tour de boucle.
void ParticleForceRegistry::updateForces(float duration)
{
	Registry::iterator i = registrations.begin(); 
		
	for (; i != registrations.end(); i++) 
	{
		i->forceGenerator->updateForce(i->particle, duration);
	}
}
