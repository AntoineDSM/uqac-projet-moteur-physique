#include "ContactResolution.h"

/*
int CollisionSphereSphere(Sphere& sphere1, Sphere& sphere2, CollisionData* data) {
	float normDistance;
	Vector3D pointContact;
	float Interpenetration;
	sphere1.body->GetPosition().get_normalization();
	sphere2.body->GetPosition().get_normalization();

	normDistance = sqrt((sphere1.body->GetPosition().x - sphere2.body->GetPosition().x) * (sphere1.body->GetPosition().x - sphere2.body->GetPosition().x) + (sphere1.body->GetPosition().y - sphere2.body->GetPosition().y) * (sphere1.body->GetPosition().y - sphere2.body->GetPosition().y) + (sphere1.body->GetPosition().z - sphere2.body->GetPosition().z) * (sphere1.body->GetPosition().z - sphere2.body->GetPosition().z)); // <--- il manque la valeur absolue // Normale de la distance entre les 2 sphère
	if ((normDistance * normDistance) < ((sphere1.m_radius + sphere2.m_radius) * (sphere1.m_radius + sphere2.m_radius)))
		Interpenetration = normDistance - (sphere1.m_radius + sphere2.m_radius);	// <--- pas sur de la formule // Somme des rayons moins la distance entre le centre des sphère

	pointContact = sphere1.body->GetPosition() + normDistance - Interpenetration; //Point sur la surface d'une sphères dans la direction du contact
}
*/

/*int CollisionSpherePlan(Sphere& sphere, Plan& plan, CollisionData* data) {


	float distance;
	Vector3D Interpenetration;
	Vector3D pointContact;
	Vector3D normal;
	//TO DO 1
	// Trouver la distance entre la sphère et le plan (prendre en compte le rayon) 𝑑=𝒑∙𝒍−𝑙 //
	// Où l est le vecteur normal au plan et l le décalage du plan.
	distance = sqrt((sphere.body->GetPosition().x - plan.body->GetPosition().x) * (sphere.body->GetPosition().x - plan.body->GetPosition().x) + (sphere.body->GetPosition().y - plan.body->GetPosition().y) * (sphere.body->GetPosition().y - plan.body->GetPosition().y) + (sphere.body->GetPosition().z - plan.body->GetPosition().z) * (sphere.body->GetPosition().z - plan.body->GetPosition().z)); // <--- il manque la valeur absolue // Normale de la distance entre les 2 sphère
	distance = (distance - plan.offset) * plan.m_normal;

	// TO DO 2
	if (distance <= 0) {

		plan.body->GetPosition().get_normalization();	// Normale direction du plan
		plan.m_normal = plan.body->GetPosition();
		Interpenetration = sphere.body->GetPosition() - plan.body->GetPosition();	// Interpénétration sois la distance entre la sphère et le plan

		pointContact = normal - Interpenetration;// Point sur la sphère en direction du contact

	}

}
*/

static int CollisionBoitePlan(const Boite& boite, const Plan& plan, CollisionData* data)
{

	if (data->contactLeft <= 0) return 0;

	for (size_t i = 0; i < 8; i++)
	{
		// Calculate the distance from the plane with dot product(vertexPos, planeNormal)
		float vertexDistance = Vector3D::scalarProduct(boite.getVertex(i), plan.getNormal()); //============================================== calculer position en fonction de la transform+offset

		// Compare this to the plane’s distance.
		if (vertexDistance <= plan.getPlaneOffset())
		{
			// Create the contact data.
			// The contact point is halfway between the vertex and the
			// plane - we multiply the direction by half the separation
			// distance and add the vertex location.
			RigidBodyContact* contact = new RigidBodyContact();
			contact->pointContact = plan.getNormal();
			contact->pointContact *= (vertexDistance - plan.getPlaneOffset());
			contact->pointContact += boite.getVertex(i);
			contact->m_contactNormal = plan.getNormal();
			contact->m_penetration = plan.getPlaneOffset() - vertexDistance;
			data->contacts.push_back(contact);
			data->addContact(1);
		}
	}
}

/*
int CollisionBoiteSphere(const Sphere& sphere, const Boite& boite, CollisionData* data) //Face-Face
{
	Vector3D pointProche;
	float distance = 0;
	// TO DO Convertire le centre du cercle en coordonné de la boîte
	// TO DO Resserrer les coordonnés du point par rapport à la boîte

	distance = boite.body->GetPosition().x;
	if (distance > boite.halfSize.x)
	{
		distance = boite.halfSize.x;
	}
	if (distance < -boite.halfSize.x)
	{
		distance = -boite.halfSize.x;
	}
	pointProche.x = distance;

	// pointProche va permettre d'extraire les données de contacts
}
*/

/*
int CollisionBoiteBoite(const Boite& boite1, const Boite& boite2, CollisionData* data)
{
	Vector3D axe[15];
	for (int i = 0; i < 15; i++) { // To Do Calculer les 15 Axes

		axe[i]; // calcule entre les 6 axes principales et 9 axes issue du produit Vectoriel de axes des deux boites
		// To Do pour chaque Axe
			// Projection des boîtes sur l,axe
			// Calculer l'interpénétration - conserver l'axe la plus petite
			// Dès que l’axe ne produit pas d’interpénétration, les objets ne sont pas en collision.


		// identifier L'Axe et générer la collision corrspondante 
		//Edge Edge ou Face Vertex.
	}
}
*/
