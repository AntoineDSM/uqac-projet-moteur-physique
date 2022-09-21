
//Date de cr�ation : 19/09/22
//Cr�er par : Victor GUIRAUD
//Date de derni�re modification : 19/09/22
//Modifi� par : Victor GUIRAUD


#include "Particle.h"


#pragma once
/** * A force generator can be asked to add a force to one or more * particles. */

class ParticleForceGenerator {
public:
 /** * Overload this in implementations of the interface to calculate * and update the force applied to the given particle. */ 

virtual void updateForce(Particle* particle, float duration) = 0;
};

