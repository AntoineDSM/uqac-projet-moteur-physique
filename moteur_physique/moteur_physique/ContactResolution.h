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

	static unsigned CollisionBoitePlan(RigidBody* boite, RigidBody* plan, CollisionData* data)
	{
		if (data->contactLeft <= 0) return 0;

		bool added = false;

		for (size_t i = 0; i < 8; i++)
		{
			//on calcule la distance entre chacun des sommets de notre cube et le plan, pour se faire on utilise un produit vectoriel qui projette la 
			//position de notre sommet sur la normal du plan.
			float vertexDistance = (float)Vector3D::scalarProduct_2(boite->GetPosition() + boite->primitiveBoite->getVertex(i), plan->primitivePlan->getNormal()); //============================================== calculer position en fonction de la transform+offset

			//si la distance est de 0 ou inferieur, nous touchons le plan.
			if (vertexDistance <= plan->primitivePlan->getPlaneOffset())
			{
				ContactRigidBody* contact = new ContactRigidBody();
				contact->m_rigidbodies[0] = boite;
				contact->m_rigidbodies[1] = plan;
				contact->m_contactPoint = plan->primitivePlan->getNormal();
				contact->m_contactPoint *= (vertexDistance - plan->primitivePlan->getPlaneOffset());
				contact->m_contactPoint = boite->GetPosition() + boite->primitiveBoite->getVertex(i);
				contact->m_contactNormal = plan->primitivePlan->getNormal();
				contact->m_penetration = plan->primitivePlan->getPlaneOffset() - vertexDistance;
				if (!added)
				{
					data->contact.push_back(contact);
					data->addContact(1);
					added = true;
				}
				contact->printInfoContact();
			}
		}
		return 0;
	}

	static unsigned CollisionBoiteBoite(const Boite& boite1, const Boite& boite2, CollisionData* data)
	{
		//pas implementee pour le moment
		return 0;
	}

	//-----------------------------------------------------------NON IMPLEMENTEES----------------------------------------------------------------------------

	//void CollisionSphereSphere(Sphere& sphere1, Sphere& sphere2) {}

	//void CollisionSpherePlan(Sphere& sphere, Plan& plan) {}

	//void CollisionBoiteSphere(const Sphere& sphere, const Boite& boite) {}
};

#endif CONTACT_RESOLUTION