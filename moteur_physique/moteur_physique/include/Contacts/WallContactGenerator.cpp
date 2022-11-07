#include "WallContactGenerator.h"

static bool inResolution = false;

void WallContactGenerator::resolveContact()
{
	for (Particle* particle : listeParticle)
	{
		double distanceParticuleA = std::sqrt((Precision::carre(particle->getPosition().x - wallElement->pointA->x)) + (Precision::carre(particle->getPosition().y - wallElement->pointA->y)) + (Precision::carre(particle->getPosition().z - wallElement->pointA->z)));
		double distanceParticuleB = std::sqrt((Precision::carre(particle->getPosition().x - wallElement->pointB->x)) + (Precision::carre(particle->getPosition().y - wallElement->pointB->y)) + (Precision::carre(particle->getPosition().z - wallElement->pointB->z)));
		double distanceAB = std::sqrt((Precision::carre(wallElement->pointA->x - wallElement->pointB->x)) + (Precision::carre(wallElement->pointA->y - wallElement->pointB->y)) + (Precision::carre(wallElement->pointA->z - wallElement->pointB->z)));

		if (distanceParticuleA + distanceParticuleB < distanceAB + 0.7)
		{
			Vector3D* nearestPoint = wallElement->listePointAB[0];
			double nearestPointDistance = std::sqrt((Precision::carre(particle->getPosition().x - nearestPoint->x)) + (Precision::carre(particle->getPosition().y - nearestPoint->y)) + (Precision::carre(particle->getPosition().z - nearestPoint->z)));;
			//tester si une particule est situé sur le vecteur séparant A et B, si oui agir en conséquence sur la vitesse de la particule (restitution, inversement de sens..)
			int cpt = 0;
			while (cpt < wallElement->listePointAB.size())
			{
				Vector3D* vector = wallElement->listePointAB[cpt];
				double distance = std::sqrt((Precision::carre(particle->getPosition().x - vector->x)) + (Precision::carre(particle->getPosition().y - vector->y)) + (Precision::carre(particle->getPosition().z - vector->z)));
				if (distance < 1)
				{
					if (distance < nearestPointDistance)
					{
						nearestPointDistance = distance;
						*nearestPoint = *vector;
					}
				}
				cpt++;
			}

			Vector3D velocity = particle->getVelocity();
			Vector3D resultante = get_resultante(particle);

			if ((particle->getVelocity().y != 0 && particle->getVelocity().x == 0 && particle->getVelocity().z == 0) || velocity == Vector3D())//la particule est au repos.
			{
				Vector3D gravity = gravityValue;
				//resoudre interpenetration
				resolvePenetration(particle, resultante);
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
				resolveVelocity(particle, resultante);
				resolvePenetration(particle, resultante);
			}
		}
	}
}

void WallContactGenerator::resolveVelocity(Particle* particle, Vector3D resultante)
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

	Vector3D newVelocity_1 = velocity;
	if (resultante.x != 0)
	{
		newVelocity_1.x *= resultante.x;
	}
	if (resultante.y != 0)
	{
		newVelocity_1.y *= resultante.y;
	}
	if (resultante.z != 0)
	{
		newVelocity_1.z *= resultante.z;
	}
	newVelocity_1 *= (1 / particle->getMass());
	particle->setVelocity(newVelocity_1);
}

void WallContactGenerator::resolvePenetration(Particle* particle, Vector3D resultante)
{
	Vector3D positionParticule = particle->getPosition();
	Vector3D newPos = positionParticule + (resultante * (double)0);
	//nous avons calculer le vecteur de direction entre le point de contact le plus proche et notre particule et nous décalons la particule d'un pas sur cette direction.
	particle->setPosition(particle->getPosition() + (resultante *(double)0));
}

Vector3D WallContactGenerator::get_resultante(Particle* particle)
{
	Vector3D normale = *wallElement->planMur;
	double angle = (particle->getVelocity().scalarProduct(normale)) / std::sqrt(particle->getVelocity().get_magnitude() * normale.get_magnitude());
	Vector3D resultante;
	int signe = 1;
	if (std::cos(angle) < 0)
	{
		signe = -1;
	}
	if (normale.x != 0)
	{
		resultante.x = normale.x * signe;
	}
	if (normale.y != 0)
	{
		resultante.y = normale.y * signe;
	}
	if (normale.z != 0)
	{
		resultante.z = normale.z * signe;
	}
	return resultante;
}