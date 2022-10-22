#pragma once

#include <vector>
#include "Utils/Timing.h"
#include "Vector3D/Vector3D.h"
#include "Particles/Particle.h"
#include "Forces/ParticleForceRegistry.h"//tous les includes de force sont dans ce header
#include "Contacts/ParticleContactResolver.h"//tous les includes de contacts sont dans ce header
#include "TimingData.h"

using namespace TimingOldMethod;
using namespace Timing;

class PhysicWorld
{

public : 

	ParticleForceRegistry* PFR;
	ParticleContactResolver* PCR;

	std::vector<Wall*> listeMurs = std::vector<Wall*>();
	std::vector<WallContactGenerator*> listeMursResolveurs = std::vector<WallContactGenerator*>();
	
	std::vector<Particle*> listeParticules = std::vector<Particle*>();
	std::vector<ParticleContact*> listeParticulesContacts = std::vector<ParticleContact*>();


	PhysicWorld()
	{
		PFR = new ParticleForceRegistry();
		PCR = new ParticleContactResolver(3);
	}

	void AfficherParticules()
	{
		for (Particle* particule : listeParticules)
		{
			particule->render();
		}
	}

	void AfficherMurs()
	{
		for (Wall* mur : listeMurs)
		{
			mur->render();
		}
	}

	void CreerContacts(Particle* newParticule)
	{
		for (Particle* particule : listeParticules)
		{
			Particle* duoParticles[2] = { particule, newParticule };
			listeParticulesContacts.push_back(new ParticleContact(duoParticles));//par defaut restitution à 0.5 et penetration à 0
		}
		for (WallContactGenerator* wallContact : listeMursResolveurs)
		{
			wallContact->listeParticle = listeParticules;
		}
	}

	void CreerMursResolveurs(Wall* newWall, float restitution = 0.8)
	{
		listeMursResolveurs.push_back(new WallContactGenerator(listeParticules, newWall, restitution));
	}

	//Rafraichissement des valeurs de position et de vitesse a valeur de temps variable, nous actualisons a la duree prise par la derniere frame pour s'executer.
	void UpdateVariousFrameRate(bool pause)//float duration)
	{
		if (pause)
		{
			//La duree de la frame precedente va nous permettre de simuler la physique de n-1, nous ne savons pas le temps que cette frame va prendre pour effectuer sa boucle de jeu.
			//Nous prenons donc volontairement une unite de retard pour la simulation.
			
			//on discretise plus que la normale//duration *=  0.0005f;//on discretise plus que la normale
			float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
			if (duration <= 0.0f) return;

			//Actualisation de la vitesse et de l'acceleration de notre particule avec l'integration en fonction du temps (temps de la frame n-1).
			for (Particle* particule : listeParticules)
			{
				particule->integrate(duration);
			}

			//Actualisation des forces appliquées à nos particules
			PFR->updateForces(duration);

			////Resolutions de l'ensemble des contacts entre nos particules
			//PCR->resolveContacts(listeParticulesContacts);

			////Resolutions des contacts en rapport avec nos murs.
			for (WallContactGenerator* wallContactGenerator : listeMursResolveurs)
			{
				wallContactGenerator->resolveContact();
			}
		}
	}

	void DisplayOpenGL()
	{
		AfficherParticules();
		AfficherMurs();
	}

	void InstancierParticule(float listParamsObj[] = {})
	{
		Particle* newParticule = new Particle();
		newParticule->setPosition(listParamsObj[1], listParamsObj[2], listParamsObj[3]);
		newParticule->setMass(listParamsObj[0]);
		newParticule->setVelocity(listParamsObj[4], listParamsObj[5], listParamsObj[6]);
		newParticule->setAcceleration(listParamsObj[7], listParamsObj[8], listParamsObj[9]);
		newParticule->setDamping(listParamsObj[10]);
		newParticule->setRadius(listParamsObj[11]);

		listeParticules.push_back(newParticule);

		CreerContacts(newParticule);
	}

	void InstancierMur(Vector3D plan, float listParamsObj[] = {})
	{
		Vector3D pointA = Vector3D(listParamsObj[0], listParamsObj[1], listParamsObj[2]);
		Vector3D pointB = Vector3D(listParamsObj[3], listParamsObj[4], listParamsObj[5]);
		Wall* newWall = new Wall(pointA, pointB, plan);
	
		listeMurs.push_back(newWall);

		CreerMursResolveurs(newWall, listParamsObj[6]);
	}

	void CreerGenerateurForce(int type, Particle* particule, float listParamsForceGenerator[] = {}, Particle* otherParticule = new Particle())//0 Buoancy, 1 drag, 2 gravity, 3 spring
	{
		switch(type)
		{
		case 0 :
		{
			ParticleBuoyancy* PFG = new ParticleBuoyancy(listParamsForceGenerator[0], listParamsForceGenerator[1], listParamsForceGenerator[2], listParamsForceGenerator[3]);
			PFR->add(particule, PFG);
			break;
		}
		case 1 :
		{
			ParticleDrag* PFG = new ParticleDrag(listParamsForceGenerator[4], listParamsForceGenerator[5]);
			PFR->add(particule, PFG);
			break;
		}
		case 2 :
		{
			Vector3D gravity = Vector3D(0, listParamsForceGenerator[6], 0);
			ParticleGravity* PFG = new ParticleGravity(gravity);
			PFR->add(particule, PFG);
			break;
		}
		case 3 :
		{
			if (!(*otherParticule == Particle()))
			{
				ParticleSpring* PFG = new ParticleSpring(otherParticule, listParamsForceGenerator[7], listParamsForceGenerator[8]);
				PFR->add(particule, PFG);
				break;
			}
			else
			{
				std::cout << "Impossible d'ajouter un particle spring avec une seconde particule non initialisée.\n";
			}
		}
		default:
		{
			Vector3D gravity = Vector3D(0, listParamsForceGenerator[6], 0);
			ParticleGravity* PFG = new ParticleGravity(gravity);
			PFR->add(particule, PFG);
			break;
		}
		}
	}

	void CreerTypeContactParticules(int type, Particle* particule1, Particle* particule2, float listParamsForceGenerator[] = {})//0 Cable, 1 Rod
	{
		int currentIndex;
		Particle* particles[2] = { particule1, particule2 };

		for(int i = 0; i < listeParticulesContacts.size(); i++)
		{
			if ((listeParticulesContacts[i]->particle[0] == particule1 || listeParticulesContacts[i]->particle[1] == particule1) && (listeParticulesContacts[i]->particle[0] == particule2 || listeParticulesContacts[i]->particle[1] == particule2))
			{
				currentIndex = i;
				break;
			}
		}
		switch (type)
		{
		case 0 :
		{
			ParticleCable newParticleContact = ParticleCable(particles, listParamsForceGenerator[0], listParamsForceGenerator[1]);
			newParticleContact.addContact(listeParticulesContacts[currentIndex]);
			break;
		}
		case 1 :
		{
			ParticleRod newParticleContact = ParticleRod(particles, listParamsForceGenerator[2]);
			newParticleContact.addContact(listeParticulesContacts[currentIndex]);
			break;
		}
		}
	}
};

