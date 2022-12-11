#pragma once

#ifndef CONTACT_RIGIDBODY
#define CONTACT_RIGIDBODY

#include "Rotations/RigidBody.h"

class ContactRigidBody
{
public:

	ContactRigidBody(RigidBody* r1, RigidBody* r2, float restitution, float penetration);
	ContactRigidBody() = default;
	~ContactRigidBody() = default;

	void resolve(float duration);

	float calculateSeperatingVelocity() const;

	RigidBody* m_rigidbodies[2];

	//elasticness
	float m_restitution = 0;

	//penetration of the contact
	float m_penetration = 0;

	Vector3D m_contactNormal;
	Vector3D m_contactPoint;

	void printInfoContact() const;

private:

	//void resolveVelocity();
	//void resolveInterpretation();
};

#endif CONTACT_RIGIDBODY

