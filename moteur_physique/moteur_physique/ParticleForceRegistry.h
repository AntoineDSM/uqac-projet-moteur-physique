//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD


#pragma once

#include "Vector3D.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace moteurJeux;


//Applique des forces � toutes les particules qui sont li�es � ces forces.

// D�tient tous les g�n�rateurs de force et les particules auxquelles ils s'appliquent.
class ParticleForceRegistry
{
protected:
	// Garde la trace d'un g�n�rateur de force et de la particule � laquelle il s'applique.

struct ParticleForceRegistration {

	Particle* particle;
	ParticleForceGenerator* forceGenerator;

}; 



//D�tient la liste des enregistrements

using Registry = std::vector<ParticleForceRegistration> ;

Registry registrations; 

public: 
	// Enregistre le g�n�rateur de force donn� � appliquer � la particule donn�e.
	
	void add(Particle* particle, ParticleForceGenerator* forceGenerator); 
	
	// Supprime la paire enregistr�e donn�e du registre. Si la paire n'est pas enregistr�e, cette m�thode n'aura aucun effet. */
	void remove(Particle* particle, ParticleForceGenerator* forceGenerator); 
	
	//Efface tous les enregistrements du registre.Cela* ne supprimera pas les particules ou les g�n�rateurs de force* eux - m�mes, seulement les enregistrements de leur connexion.* /
    void clear();

	//Appelle tous les g�n�rateurs de force pour mettre � jour les forces de leurs particules correspondantes.* /

	void updateForces(float duration);
}; 





