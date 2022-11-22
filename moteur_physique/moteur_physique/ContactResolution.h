#ifndef COLLISIONRESOLUTION_H
#define COLLISIONRESOLUTION_H
#pragma once

#include "Sphere.h"
#include "Plan.h"
#include "Boite.h"


void CollisionSphereSphere(const Sphere& sphere1, const Sphere& sphere2) {
	float distance = 0.0;
	//TO DO Normale de la distance entre les 2 sphère

	//TO DO Somme des rayons moins la distance entre le centre des sphère

	//TO DO Point sur la surface d,une sphères dans la direction du contact
}

void CollisionSpherePlan(const Sphere& sphere, const Plan& plan) {

	float distance = 0.0;
	//TO DO 1
	// Trouver la distance entre la sphère et le plan (prendre en compte le rayon) 𝑑=𝒑∙𝒍−𝑙
	// Où l est le vecteur normal au plan et l le décalage du planc
	//distance = sphere.radius * plan.normal - plan.offset;


	if (distance < 0) {
		// TO DO 2
	// Normale direction du plan

	// Interpénétration sois la distance entre la sphère et le plan

	// Point sur la sphère en direction du contact

	}

}

void CollisionBoitePlan() {

	// Peut générer plusieurs contacts.
	// Consiste à valider chacun despoints de la boîte par rapport au plan en utilisant la formule : 𝑑=𝒑∙𝒍−𝑙

}

void CollisionBoiteSphere(const Sphere& sphere, const Boite& boite) //Face-Face
{
	Vector3D pointProche;
	float distance = 0;
	// TO DO Convertire ke centre du cercle en coordonné de la boîte
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
	// To Do Calculer les 15 Axes
	// To Do pour chaque Axe
		// Projection des boîtes sur l,axe
		// Calculer l'interpénétration - conserver l'axe la plus petite
		// Dès que l’axe ne produit pas d’interpénétration, les objets ne sont pas en collision.
	// identifier L'Axe et générer la collision corrspondante 
		//Edge Edge ou Face Vertex.
}

#endif