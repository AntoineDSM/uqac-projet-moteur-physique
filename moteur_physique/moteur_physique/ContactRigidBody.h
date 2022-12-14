#pragma once

#ifndef CONTACT_RIGIDBODY
#define CONTACT_RIGIDBODY

#include "Rotations/RigidBody.h"

//Class permettant de garder les elements relatifs a un contact entre deux objets, nous pouvons a partir de ce contact le resoudre et donc appliquer les
//modifications physiques necessaires.
class ContactRigidBody
{

public:

	//restitution du contact
	float m_restitution = 1;

	//interpenetration entre nos deux rigidbodies
	float m_penetration = 0;

	//normal au point de contact
	Vector3D m_contactNormal;

	//point de contact
	Vector3D m_contactPoint;

	//nous gardons une reference vers nos deux rigidbodies
	RigidBody* m_rigidbodies[2] = { new  RigidBody() };

	//constructeur par defaut
	ContactRigidBody()
	{
		//rien a ajouter
	}

	//constructeur avec passage de parametres
	ContactRigidBody(RigidBody* r1, RigidBody* r2, float restitution, float penetration);

	//---------------------------------------------------METHODES PUBLIQUES-----------------------------------------------------------

	//permet de resoudre le contact et donc d'appliquer les modifications necessaires a nos rigidbodies
	void resolve(float duration);

	//calcule difference de velocite entre nos objets
	float calculateSeperatingVelocity() const;

	//permet d'afficher en console les elements relatifs au contact afin de verifier
	void printInfoContact() const;
};


#endif CONTACT_RIGIDBODY

