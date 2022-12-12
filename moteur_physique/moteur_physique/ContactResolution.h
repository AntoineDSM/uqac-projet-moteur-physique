#pragma once

#ifndef CONTACT_RESOLUTION
#define CONTACT_RESOLUTION

#include "Plan.h"
#include "Boite.h"
#include "ContactRigidBody.h"

//------------------------------------------------------------------COLLISION DATA------------------------------------------------------------------------

struct CollisionData 
{
	//On recupere l'ensemble des contacts generes
	std::vector<ContactRigidBody*> contact = std::vector<ContactRigidBody*>();

	//Combien de contact il nous reste a resoudre
	int contactLeft = 0;

	void addContact(int count)
	{
		contactLeft -= count;
	}
};

//------------------------------------------------------------------COLLISION RESOLUTION------------------------------------------------------------------------

//Cette classe nous permettra de detecter le type du contact face auquel nous sommes.
//Ne devons a minima implementer un contact boite->plan, sphere n'est donc pas developper et est exclu du projet pour le moment.
class ContactResolutions 
{

public:

	//-----------------------------------------------------------IMPLEMENTEES----------------------------------------------------------------------------

	static unsigned CollisionBoitePlan(const Boite& boite, const Plan& plan, CollisionData* data)
	{
		if (data->contactLeft <= 0) return 0;

		for (size_t i = 0; i < 8; i++)
		{
			// Calculate the distance from the plane with dot product(vertexPos, planeNormal)
			float vertexDistance = (float)Vector3D::scalarProduct_2(boite.getVertex(i), plan.getNormal()); //============================================== calculer position en fonction de la transform+offset

			// Compare this to the plane’s distance.
			if (vertexDistance <= plan.getPlaneOffset())
			{
				// Create the contact data.
				// The contact point is halfway between the vertex and the
				// plane - we multiply the direction by half the separation
				// distance and add the vertex location.
				ContactRigidBody* contact = new ContactRigidBody();
				contact->m_contactPoint = plan.getNormal();
				contact->m_contactPoint *= (vertexDistance - plan.getPlaneOffset());
				contact->m_contactPoint += boite.getVertex(i);
				contact->m_contactNormal = plan.getNormal();
				contact->m_penetration = plan.getPlaneOffset() - vertexDistance;
				data->contact.push_back(contact);
				data->addContact(1);
			}
		}
		return 0;
	}

	static unsigned CollisionBoiteBoite(const Boite& boite1, const Boite& boite2, CollisionData* data)
	{
		//pas implemente pour le moment
		return 0;
	}

	//-----------------------------------------------------------NON IMPLEMENTEES----------------------------------------------------------------------------

	//void CollisionSphereSphere(Sphere& sphere1, Sphere& sphere2) {}

	//void CollisionSpherePlan(Sphere& sphere, Plan& plan) {}

	//void CollisionBoiteSphere(const Sphere& sphere, const Boite& boite) {}
};

#endif CONTACT_RESOLUTION