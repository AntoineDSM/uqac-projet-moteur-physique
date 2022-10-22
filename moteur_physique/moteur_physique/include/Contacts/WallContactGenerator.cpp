#include "WallContactGenerator.h"


void WallContactGenerator::resolveContact()
{
	for (Particle* particle : listeParticle)
	{
		//tester si une particule est situé sur le vecteur séparant A et B, si oui agir en conséquence sur la vitesse de la particule (restitution, inversement de sens..)
		for (Vector3D* vector : wallElement->listePointAB)
		{
			double distance = std::sqrt((Precision::carre(particle->getPosition().x - vector->x)) + (Precision::carre(particle->getPosition().y - vector->y)) + (Precision::carre(particle->getPosition().z - vector->z)));
			if (distance < 0.1)
			{
				if (particle->getVelocity() == gravityValue)//la particule est au repos.
				{
					Vector3D gravity = gravityValue;
					//resoudre interpenetration
					resolvePenetration(particle, vector);
					//mettre velocite a 0 (equivaut a appliquer la 3eme loi de newton en imaginant que la mur applique une force de - gravité sur notre particule
					particle->setVelocity(Vector3D());
					//si notre mur n'est pas droit, changer la velocite de la particule dans la direction du mur (sur l'axe X).
					if (wallElement->vecteurAB->y != 0)
					{
						particle->setVelocity(gravity * particle->getMass() * *wallElement->vecteurAB);
					}
				}
				else
				{
					resolveVelocity(particle, vector);
				}
			}
		}
	}
}

void WallContactGenerator::resolveVelocity(Particle* particle, Vector3D* pointContact)
{
	Vector3D velocity = particle->getVelocity();

	if (restitution == 1)//parfaitement elastique
	{
		//seperatingVelocity reste la meme
	}
	else if (restitution == 0)//parfaitement inélastique
	{
		velocity = Vector3D();
	}
	else if (restitution > 0 && restitution < 1)//elastique
	{
		velocity *= restitution;
	}

	//calcul du vecteur normal à nos objets
	Vector3D normal = Vector3D::vectorialProduct(particle->getVelocity(), *pointContact);

	Vector3D newVelocity_1 = velocity - normal * (1 / particle->getMass());

	particle->setVelocity(newVelocity_1);
}

void WallContactGenerator::resolvePenetration(Particle* particle, Vector3D* pointContact)
{
	Vector3D direction = *pointContact - particle->getPosition();
	direction.get_normalization();
	//nous avons calculer le vecteur de direction entre le point de contact le plus proche et notre particule et nous décalons la particule d'un pas sur cette direction.
	particle->setPosition(particle->getPosition() - (direction * 0.5));
}