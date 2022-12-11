#include "ContactResolution.h"

//-----------------------------------------------------------------------IMPLEMENTEES--------------------------------------------------------------------


//-----------------------------------------------------------------------NON IMPLEMENTEES--------------------------------------------------------------------

/*
void CollisionSphereSphere(Sphere& sphere1, Sphere& sphere2) {
	float normDistance;
	Vector3D pointContact;
	float Interpenetration;
	sphere1.body->GetPosition().get_normalization();
	sphere2.body->GetPosition().get_normalization();

	normDistance = sqrt((sphere1.body->GetPosition().x - sphere2.body->GetPosition().x) * (sphere1.body->GetPosition().x - sphere2.body->GetPosition().x) + (sphere1.body->GetPosition().y - sphere2.body->GetPosition().y) * (sphere1.body->GetPosition().y - sphere2.body->GetPosition().y) + (sphere1.body->GetPosition().z - sphere2.body->GetPosition().z) * (sphere1.body->GetPosition().z - sphere2.body->GetPosition().z)); // <--- il manque la valeur absolue // Normale de la distance entre les 2 sphère
	if ((normDistance * normDistance) < ((sphere1.radius + sphere2.radius) * (sphere1.radius + sphere2.radius)))
		Interpenetration = normDistance - (sphere1.radius + sphere2.radius);	// <--- pas sur de la formule // Somme des rayons moins la distance entre le centre des sphère

	pointContact = sphere1.body->GetPosition() + normDistance - Interpenetration; //Point sur la surface d'une sphères dans la direction du contact
}

void CollisionSpherePlan(Sphere& sphere, Plan& plan) {


	float distance;
	Vector3D Interpenetration;
	Vector3D pointContact;
	Vector3D normal;
	//TO DO 1
	// Trouver la distance entre la sphère et le plan (prendre en compte le rayon) 𝑑=𝒑∙𝒍−𝑙 //
	// Où l est le vecteur normal au plan et l le décalage du plan.
	distance = sqrt((sphere.body->GetPosition().x - plan.body->GetPosition().x) * (sphere.body->GetPosition().x - plan.body->GetPosition().x) + (sphere.body->GetPosition().y - plan.body->GetPosition().y) * (sphere.body->GetPosition().y - plan.body->GetPosition().y) + (sphere.body->GetPosition().z - plan.body->GetPosition().z) * (sphere.body->GetPosition().z - plan.body->GetPosition().z)); // <--- il manque la valeur absolue // Normale de la distance entre les 2 sphère
	distance = (distance - plan.offset) * plan.normal;

	// TO DO 2
	if (distance.isNULL) {

		plan.body->GetPosition().get_normalization();	// Normale direction du plan
		plan.normal = plan.body->GetPosition();
		Interpenetration = sphere.body->GetPosition() - plan.body->GetPosition();	// Interpénétration sois la distance entre la sphère et le plan

		pointContact = normal - Interpenetration;// Point sur la sphère en direction du contact

	}
}

void CollisionBoiteSphere(const Sphere& sphere, const Boite& boite) //Face-Face
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
