//Date de création : 16/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD


#include <stdio.h>
#include "Particle.h"

using namespace Particle;

class Ballistic {


	enum ShotType
	{
		UNUSED ,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER
	};

	enum AmmoRound {
		//je sais pas trop quoi mettre dedans
		//j'ai déduis la structure depuis les variables et fonction en dessous
	ShotType shot;
	double startTime;
	Particle particle;

	};


	// Update the physics of each particle in turn. 
	for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++) {
		if (shot->type != UNUSED) {

			// Run the physics. 
			shot->particle.integrate(duration);
		}
	}
	// Check to see if the particle is now invalid. 
	if (shot->particle.getPosition().y < 0.0f || shot->startTime + 5000 < TimingData::get().lastFrameTimestamp || shot->particle.getPosition().z > 200.0f)
	{
		// We simply set the shot type to be unused, so the // memory it occupies can be reused by another shot.
		shot->type = UNUSED;

	}


	
	ShotType currentShotType;

	switch (currentShotType) {

	

	case PISTOL: 
		shot-particle.setMass(2.0f); // 2.0kg // Equivalent de shot.particle.setMass(2.0f);
		shot->particle.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s 
		shot->particle.setAcceleration(0.0f, -1.0f, 0.0f);
		shot->particle.setDamping(0.99f);
		break;
	case ARTILLERY: 
		shot->particle.setMass(200.0f); // 200.0kg 
		shot->particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s 
		shot->particle.setAcceleration(0.0f, -20.0f, 0.0f);
	    shot->particle.setDamping(0.99f); 
		break; 
	case FIREBALL: 
		shot->particle.setMass(1.0f); // 1.0kg - mostly blast damage 											  
        shot->particle.setVelocity(0.0f, 0.0f, 10.0f); // 5m/s 
		shot->particle.setAcceleration(0.0f, 0.6f, 0.0f); // Floats up 
		shot->particle.setDamping(0.9f); 
		break; 
	case LASER: // Note that this is the kind of laser bolt seen in films, // not a realistic laser beam! 
		shot->particle.setMass(0.1f); // 0.1kg - almost no weight 
		shot->particle.setVelocity(0.0f, .0f, 100.0f); // 100m/s 
		shot->particle.setAcceleration(0.0f, 0.0f, 0.0f); // No gravity 
		shot->particle.setDamping(0.99f); 
		break; 
	
	}

	// Set the data common to all particle types. 
	shot->particle.setPosition(0.0f, 1.5f, 0.0f); 
	shot->startTime = TimingData::get().lastFrameTimestamp; 
	shot->type = currentShotType; 

	// Clear the force accumulators. 
	shot->particle.clearAccumulator();
	
};