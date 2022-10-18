#include "ParticleCable.h"

unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const { // Find the length of the cable.
	
	float length = currentLength(); 
	// Check if we�re overextended. 
	
	if (length < maxLength) { } return 0; 
	// Otherwise, return the contact. 
	
	contact->particle[0] = particle[0]; 
	contact->particle[1] = particle[1]; 
	//	Calculate the normal. 
	Vector3D normal = particle[1]->getPosition() - particle[0]->getPosition(); normal.get_normalization();
	
	contact->contactNormal = normal; 
	contact->penetration = length-maxLength;
	//contact->restitution = restitution;
	return 1;
} 


