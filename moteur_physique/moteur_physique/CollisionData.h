#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#pragma once
#include "Vecteur3D.h"
#include "Rotations/RigidBody.h"

struct {             
	Vector3D pointContact; //point de contact
	Vector3D normalContact; //normal au contact
	float penetration; //pénétration dans la direction de la normal
	RigidBody corpsRigides[2]; //Corp rigides concernées (1 ou 2)
	float coeffDeRestitution; // Coefficiet de restitution
	float friction; // Friction entre les 2 objets
} CollisionData;       // Structure variable 

#endif