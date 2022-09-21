//Date de création : 16/09/22
//Créer par : Victor GUIRAUD
//Date de dernière modification : 18/09/22
//Modifié par : Victor GUIRAUD


#include <stdio.h>
#include "Particle.h"
#include "Timing.h"
#include "Vector3D.h"

//using namespace Particle;
using namespace moteurJeux;
using namespace TimingDate;

class Ballistic {

	// Enumeration of each types of shot shoot.
	enum ShotType
	{
		UNUSED,
		PISTOL,
		ARTILLERY,
		FIREBALL,
		LASER
	};
	// Structure of an ammo round.
	struct AmmoRound {
		//je sais pas trop quoi mettre dedans
		//j'ai déduis la structure depuis les variables et fonction en dessous

		// Shot type.
		ShotType type;
		// Start time of the shot.
		double startTime;
		// Particle linked to the shot.
		Particle particle;

	};
	// Amount of ammo shot.
	const static unsigned ammoRounds = 16;
	// Aimple array of ammo rounds.
	AmmoRound ammo[ammoRounds];
	// get the last frame duration of the shot for the "update" function as we use it to fire another shot.
	float duration = (float)TimingData::get().lastFrameDuration;
	// A shot.
	AmmoRound *shot;
	
	// The "shoot" function.
	void shoot() {


		// Update the physics of each particle in turn. 
		for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++) {
			if (shot->type != UNUSED) {

				// Run the physics. 
				shot->particle.integrate(duration);
			}
		}

		// If we didn't find a round, then exit - we can't fire.
		if (shot >= ammo + ammoRounds) return;

		// Check to see if the particle is now invalid. 
		if (shot->particle.getPosition().y < 0.0f || shot->startTime + 5000 < TimingData::get().lastFrameTimestamp || shot->particle.getPosition().z > 200.0f)
		{
			// We simply set the shot type to be unused, so the  memory it occupies can be reused by another shot.
			shot->type = UNUSED;

		}

		// We shoot.
		shoot();

		// Initialise the type of the current shot.
		ShotType currentShotType;

		// Apply differents settings depending on the type of the shot.
		switch (currentShotType) {

		case PISTOL:
			shot->particle.setMass(2.0f); // 2.0kg // Equivalent of shot.particle.setMass(2.0f);
			shot->particle.setVelocity(0.0f, 0.0f, 35.0f); // 35m/s 
			shot->particle.setAcceleration(0.0f, -1.0f, 0.0f); // Floats down
			shot->particle.setDamping(0.99f);
			break;
		case ARTILLERY:
			shot->particle.setMass(200.0f); // 200.0kg 
			shot->particle.setVelocity(0.0f, 30.0f, 40.0f); // 50m/s 
			shot->particle.setAcceleration(0.0f, -20.0f, 0.0f); // Goes down
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
			shot->particle.setVelocity(0.0f, 0.0f, 100.0f); // 100m/s 
			shot->particle.setAcceleration(0.0f, 0.0f, 0.0f); // No gravity 
			shot->particle.setDamping(0.99f);
			break;

		default: return ;

		}

		// Set the data common to all particle types. 
		shot->particle.setPosition(0.0f, 1.5f, 0.0f);
		shot->startTime = TimingData::get().lastFrameTimestamp;
		shot->type = currentShotType;

		// Clear the force accumulators. 
		shot->particle.clearAccumulators();
	}
	//la boucle de jeu?
	//faire evoluer avec un pas de temps discret (plus petit, plus haute precision, il faut donc trouver un compromis en essayant)
	void update()
	{
		// Find the duration of the last frame in seconds
		float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
		if (duration <= 0.0f) return;
		for (AmmoRound* shot = ammo; shot < ammo + ammoRounds; shot++)
		{
			if (shot->type != UNUSED)
			{
				//TODO Update the shot
			}
		}
		//Application::update();
	}
	
};