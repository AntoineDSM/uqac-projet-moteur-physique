
#include "ParticleContact.h"
#include "../include/Particles/Particle.h"
#include "../include/Vector3D/Vector3D.h"

using namespace moteurJeux;

ParticleContact::ParticleContact(Particle* particles[2], float restitution, float penetration) : restitution(restitution), penetration(penetration)
{
	particle[0] = particles[0];
	particle[1] = particles[1];
}

Vector3D ParticleContact::calculatingSeparatingVelocity() 
{
	Vector3D velocity = particle[0]->getVelocity() - particle[1]->getVelocity();
	return velocity;
};

void ParticleContact::resolve()// si nous resolvons les contacts ici, l'inversion de vitesse et l'ajustement de la position sont instantan�s, la dur�e d'une frame n'a pas grand chose a faire la ? rien ne d�pend du temps c'est une impulsion
{
	if (resolveInterpretation())
	{
		resolveVelocity();
	}
};

void ParticleContact::resolveVelocity() 
{
	if (penetration != 0 && restitution == 1)//nous sommes face a une tige
	{
		Vector3D velocity1 = particle[0]->getVelocity();
		Vector3D velocity2 = particle[1]->getVelocity();
		velocity1 = moteurJeux::Vector3D::get_abs(velocity1);
		velocity2 = moteurJeux::Vector3D::get_abs(velocity2);
		Vector3D velocity = velocity1 - velocity2;
		particle[0]->setVelocity(velocity);
		particle[1]->setVelocity(velocity);
		return;
	}

	Vector3D seperatingVelocity = calculatingSeparatingVelocity();

	if (restitution == 1)//parfaitement elastique
	{
		//seperatingVelocity reste la meme
	}
	else if (restitution == 0)//parfaitement in�lastique
	{
		seperatingVelocity = Vector3D();
	}
	else if (restitution > 0 && restitution < 1)//elastique
	{
		seperatingVelocity *= restitution;
	}
	
	//difference de vitesse entre nos deux objets
	Vector3D velocity = particle[0]->getVelocity() - particle[1]->getVelocity();
	//calcul du vecteur normal � nos objets
	Vector3D normal = Vector3D::vectorialProduct(particle[0]->getVelocity(),particle[1]->getVelocity());
	if (normal.get_magnitude() == 0 || penetration != 0)//les velocit� sont parall�les donc on utilise l'une d'entre elle a la place ou nous avons tige/cable
	{
		Vector3D velocity1 = particle[0]->getVelocity();
		velocity1 = moteurJeux::Vector3D::get_normalization(velocity1);
		normal = velocity1;
	}
	//calcul du facteur k, cf document cours.
	double k = normal.scalarProduct(seperatingVelocity * ((double)restitution + 1)) / ((1/particle[0]->getMass() + 1/particle[1]->getMass()));
	Vector3D newVelocity_1 = particle[0]->getVelocity() + (normal * k ) * (1/particle[0]->getMass()) * (double)(-1);
	Vector3D newVelocity_2 = particle[1]->getVelocity() - (normal * k) * (1/particle[1]->getMass()) * (double)(-1);


	particle[0]->setVelocity(newVelocity_1);
	particle[1]->setVelocity(newVelocity_2);
};

bool ParticleContact::resolveInterpretation()
{
	//vecteur normal entre nos deux objets
	Vector3D normal = Vector3D::vectorialProduct(particle[0]->getVelocity(), particle[1]->getVelocity());
	if (normal.get_magnitude() == 0)//les velocit� sont parall�les donc on utilise l'une d'entre elle a la place
	{
		Vector3D velocity1 = particle[0]->getVelocity();
		velocity1 = moteurJeux::Vector3D::get_normalization(velocity1);
		normal = velocity1;
	}

	//vecteur de direction entre les deux objets
	Vector3D vectorBetweenParticles = particle[1]->getPosition() - particle[0]->getPosition();
	vectorBetweenParticles.get_normalization();
	
	//extreme de notre particle dans la direction de la seconde particule
	Vector3D contactPointParticle_0 = particle[0]->getPosition() + vectorBetweenParticles * particle[0]->getRadius();
	//distance entre cet extreme et le centre seconde particule
	double distance = std::sqrt((Precision::carre(particle[1]->getPosition().x-contactPointParticle_0.x))+(Precision::carre(particle[1]->getPosition().y-contactPointParticle_0.y))+(Precision::carre(particle[1]->getPosition().z-contactPointParticle_0.z)));

	if (distance > penetration && restitution == 1)//nous sommes face � une tige
	{
		double dif = distance - penetration;
		Vector3D direction = particle[0]->getPosition() - particle[1]->getPosition();
		direction = moteurJeux::Vector3D::get_normalization(direction);
		Vector3D newPosP1 = particle[0]->getPosition();
		newPosP1.addScaledVector(direction, (double)(-1) * (dif / 2));
		Vector3D newPosP2 = particle[1]->getPosition();
		newPosP2.addScaledVector(direction, (dif / 2));
		particle[0]->setPosition(newPosP1);
		particle[1]->setPosition(newPosP2);
		return true;
	}

	if (distance > penetration && restitution != 1)//nous sommes face a un cable
	{
		return true;
	}

	if (distance < 2 * particle[1]->getRadius())
	{
		//nos objets se touchent
		double tailleInterpenetration = particle[1]->getRadius() - distance;
		double masse_1 = particle[0]->getMass();
		double masse_2 = particle[1]->getMass();
		Vector3D newPosP1 = particle[0]->getPosition();
		newPosP1.addScaledVector(normal, tailleInterpenetration * (masse_1 / (masse_1 + masse_2)));
		Vector3D newPosP2 = particle[1]->getPosition();
		newPosP2.addScaledVector(normal, tailleInterpenetration * (masse_1 / (masse_1 + masse_2)) * (double)(-1));
		particle[0]->setPosition(newPosP1);
		particle[1]->setPosition(newPosP2);
		return true;
	}

	return false;
};

bool ParticleContact::separatingDistance()
{
	//vecteur de direction entre les deux objets
	Vector3D vectorBetweenParticles = particle[1]->getPosition() - particle[0]->getPosition();
	vectorBetweenParticles.get_normalization();
	Vector3D contactPointParticle_0 = particle[0]->getPosition() + vectorBetweenParticles * particle[0]->getRadius();
	double distance = std::sqrt((Precision::carre(particle[1]->getPosition().x - contactPointParticle_0.x)) + (Precision::carre(particle[1]->getPosition().y - contactPointParticle_0.y)) + (Precision::carre(particle[1]->getPosition().z - contactPointParticle_0.z)));
	if (distance < 2 * particle[1]->getRadius())
	{
		return true;
	}
	else
	{
		return false;
	}
}
