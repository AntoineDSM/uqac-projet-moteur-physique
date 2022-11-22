#ifndef COLLISIONRESOLUTION_H
#define COLLISIONRESOLUTION_H
#pragma once

#include "Sphere.h"
#include "Plan.h"
#include "Boite.h"


void CollisionSphereSphere(const Sphere& sphere1, const Sphere& sphere2) {
	Vector3D normDistance;
	Vector3D pointContact;
	float Interpenetration = 0.0;

	normDistance = Normalize(sphere1.body->GetPosition() - sphere2.body->GetPosition()); //TO DO Normale de la distance entre les 2 sphère
	
	Interpenetration = sphere1.radius + sphere2.radius - (sphere1.body->GetPosition().x - sphere2.body->GetPosition().x);	//TO DO Somme des rayons moins la distance entre le centre des sphère

	pointContact = normDistance - Interpenetration; //TO DO Point sur la surface d,une sphères dans la direction du contact
}

void CollisionSpherePlan(const Sphere& sphere, const Plan& plan) {

	
	float distance = 0.0;
	float Interpénétration = 0.0;
	Vector3D pointContact;
	Vector3D normal;
	//TO DO 1
	// Trouver la distance entre la sphère et le plan (prendre en compte le rayon) 𝑑=𝒑∙𝒍−𝑙
	// Où l est le vecteur normal au plan et l le décalage du plan.
	distance = (sphere.body->GetPosition().x +sphere.radius) * plan.normal.x - plan.offset;

	// TO DO 2
	if (distance < 0) {
		
		normal = Normalize(plan.normal);	// Normale direction du plan

		Interpénétration = sphere.body->GetPosition().x - plan.body->GetPosition().x;	// Interpénétration sois la distance entre la sphère et le plan

		pointContact = normal - Interpénétration;// Point sur la sphère en direction du contact

	}

}

void CollisionBoitePlan(const Boite& boite, const Plan& plan) {

	Vector3D pointContact;

	// Peut générer plusieurs contacts.
	
	for (int i = 0; i < 16; i++)
	{
				// Consiste à valider chacun des points de la boîte par rapport au plan en utilisant la formule : 𝑑=𝒑∙𝒍−𝑙
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

void CollisionBoiteBoite(const Boite& boite1, const Boite& boite2)
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

Vector3D Normalize(Vector3D v) {
	float result = v.x * v.x + v.y * v.y  + v.z * v.z;
	if (result == 0) {
		return;
	}
	result = ((float)1.0) / sqrt(result);
	v.x *= result;
	v.y *= result;
	v.z *= result;
	
	return v;
}
#endif