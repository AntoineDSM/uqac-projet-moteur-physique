#pragma once

#include "Rotations/RigidBody.h"
#include "Vector3D/Vector3D.h"

//Vu que nous avons un particule contact, nous aurions pu les faire hériter d'un type generique, 
//pour des soucis de temps et d'adaptation de code nous restons avec cette maniere moins optimisee.
class RigidBodyContact
{

public:

	RigidBodyContact()
	{
		m_rigidbodies[0] = new RigidBody();
		m_rigidbodies[1] = new RigidBody();
		m_restitution = 0;
		m_penetration = 0;
		m_contactNormal = Vector3D(0, 0, 0);
		pointContact = Vector3D(0, 0, 0);
		friction = 0;
	}
	RigidBodyContact(RigidBody* r1, RigidBody* r2, float restitution, float penetration);
	~RigidBodyContact() = default;

	void resolve(float duration);

	float calculateSeperatingVelocity() const;

	RigidBody* m_rigidbodies[2];

	//elasticness
	float m_restitution;

	//penetration of the contact
	float m_penetration;

	Vector3D m_contactNormal;

	Vector3D pointContact; //point de contact

	float friction; // Friction entre les 2 objets

	void printInfoContact() const;

};

