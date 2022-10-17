//Date de création : 19/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 19/09/22
//Modifié par : Victor GUIRAUD


#pragma once

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace moteurJeux;


//Applique des forces à toutes les particules qui sont liées à ces forces.

// Détient tous les générateurs de force et les particules auxquelles ils s'appliquent.
class ParticleForceRegistry
{
protected:
	// Garde la trace d'un générateur de force et de la particule à laquelle il s'applique.

struct ParticleForceRegistration {

	Particle* particle;
	ParticleForceGenerator* forceGenerator;

}; 



//Détient la liste des enregistrements

using Registry = std::vector<ParticleForceRegistration> ;

Registry registrations; 

public: 
	// Enregistre le générateur de force donné à appliquer à la particule donnée.
	
	void add(Particle* particle, ParticleForceGenerator* forceGenerator); 
	
	// Supprime la paire enregistrée donnée du registre. Si la paire n'est pas enregistrée, cette méthode n'aura aucun effet. */
	void remove(Particle* particle, ParticleForceGenerator* forceGenerator); 
	
	//Efface tous les enregistrements du registre.Cela* ne supprimera pas les particules ou les générateurs de force* eux - mêmes, seulement les enregistrements de leur connexion.* /
    void clear();

	//Appelle tous les générateurs de force pour mettre à jour les forces de leurs particules correspondantes.* /

	void updateForces(float duration);
}; 





