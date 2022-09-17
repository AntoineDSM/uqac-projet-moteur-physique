
//Date de création :
//Créer par :
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#include "assert.h"
#include "Particle.h"
#include "Vector3D.h"



using namespace moteurJeux;
using namespace Particle;

void integrate(double duration) { 
	// We don’t integrate things with infinite mass.
	if (inverseMass <= 0.0f) return; assert(duration > 0.0); 
	// Update linear position. 
	position.addScaledVector(velocity, duration); 
	
	// Work out the acceleration from the force. 
	// (We’ll add to this vector when we come to generate forces.) 
	Vector3D resultingAcc = acceleration; 
	// Update linear velocity from the acceleration. 
	velocity.addScaledVector(resultingAcc, duration); 
	// Impose drag. 
	velocity *= real_pow(damping, duration); 
} 
    // Clear the forces. 
    clearAccumulator();
	
	