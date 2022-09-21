

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


//Apply forces to all particles that are linked to this forces

/** * Holds all the force generators and the particles that they apply to. */
class ParticleForceRegistry
{
protected:
/* Keeps track of one force generator and the particle it * applies to. */ 

struct ParticleForceRegistration {

	Particle* particle;
	ParticleForceGenerator* forceGenerator;

}; 



/** * Holds the list of registrations. */ 

using Registry = std::vector<ParticleForceRegistration> ;

Registry registrations; 

public: 
	/** * Registers the given force generator to apply to the * given particle. */ 
	
	void add(Particle* particle, ParticleForceGenerator* fg); 
	
	/** * Removes the given registered pair from the registry. * If the pair is not registered, this method will have * no effect. */ 
	
	void remove(Particle* particle, ParticleForceGenerator* fg); 
	
	/** * Clears all registrations from the registry. This will * not delete the particles or the force generators * themselves, just the records of their connection. */ 
	void clear();
}; 

/** * Calls all the force generators to update the forces of * their corresponding particles. */ 


void updateForces(float duration);



