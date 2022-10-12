//Date de création :
//Créer par : 
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#pragma once

#include "math.h"
#include "Vector3D.h"
#include "Particle.h"

#ifndef PARTICLECONTACT_HPP
#define PARTICLECONTACT_HPP


class ParticleContact {

public:
	// Particle[0] => Particle A
	// Particle[0] => Particle B - could be nullptr





	Particle* particle[2];

	// value between 0 - 1
	// define the elasticness of the collision  
	float restitution;

	//distance of penetration of the contact
	float penetration;

	// normal of the vector
	Vector3D contactNormal;

	//resolve velocity and interpenetration

	void resolve(float duration);


	// return the separation velocity of the particules

	float calculatingSeparatingVelocity();

	//handle impulse for this collision
	void resolveVelocity();


	//handle interpenetration of the collision

	void resolveInterpretation();




};

#endif PARTICLECONTACT_HPP
