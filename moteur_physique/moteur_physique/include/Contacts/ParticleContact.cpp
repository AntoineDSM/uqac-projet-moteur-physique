
#include "ParticleContact.h"
#include "../include/Particles/Particle.h"
#include "../include/Vector3D/Vector3D.h"

using namespace moteurJeux;

ParticleContact::ParticleContact(Particle* particles[2], float restitution, float penetration) : restitution(restitution), penetration(penetration)
{
	particle[0] = particles[0];
	particle[1] = particles[1];
}

float ParticleContact::calculatingSeparatingVelocity() 
{
	float vs;

	Vector3D velocity = particle[0]->getVelocity() - particle[1]->getVelocity();
	Vector3D position = particle[0]->getPosition() - particle[1]->getPosition();
	Vector3D normalizedVector = Vector3D::get_normalization(position);
	vs = velocity.scalarProduct(position);

	return vs;
};

void ParticleContact::resolve()// si nous resolvons les contacts ici, l'inversion de vitesse et l'ajustement de la position sont instantanés, la durée d'une frame n'a pas grand chose a faire la ? rien ne dépend du temps c'est une impulsion
{
	resolveInterpretation();
	resolveVelocity();
};

void ParticleContact::resolveVelocity() 
{
	float seperatingVelocity = calculatingSeparatingVelocity();

	if (restitution == 1)//parfaitement elastique
	{
		//seperatingVelocity reste la meme
	}
	else if (restitution == 0)//parfaitement inélastique
	{
		seperatingVelocity = 0;
	}
	else if (restitution > 0 && restitution < 1)//elastique
	{
		seperatingVelocity *= restitution;
	}
	
	//difference de vitesse entre nos deux objets
	Vector3D velocity = particle[0]->getVelocity() - particle[1]->getVelocity();
	//calcul du vecteur normal à nos objets
	Vector3D normal = Vector3D::vectorialProduct(particle[0]->getVelocity(),particle[1]->getVelocity());
	//calcul du facteur k, cf document cours.
	double k = normal.scalarProduct(velocity * ((double)restitution + 1)) / ((1/particle[0]->getMass() + 1/particle[1]->getMass()));

	Vector3D newVelocity_1 = particle[0]->getVelocity() - (normal * k ) * (1/particle[0]->getMass()) * seperatingVelocity;
	Vector3D newVelocity_2 = particle[1]->getVelocity() - (normal * k) * (1/particle[1]->getMass()) * seperatingVelocity;

	particle[0]->setVelocity(newVelocity_1);
	particle[1]->setVelocity(newVelocity_2);
};

float ParticleContact::resolveInterpretation()
{
	//vecteur normal entre nos deux objets
	Vector3D normal = Vector3D::vectorialProduct(particle[0]->getVelocity(), particle[1]->getVelocity());

	//vecteur de direction entre les deux objets
	Vector3D vectorBetweenParticles = particle[1]->getPosition() - particle[0]->getPosition();
	vectorBetweenParticles.get_normalization();
	
	//extreme de notre particle dans la direction de la seconde particule
	Vector3D contactPointParticle_0 = particle[0]->getPosition() + vectorBetweenParticles * particle[0]->getRadius();
	//distance entre cet extreme et le centre seconde particule
	double distance = std::sqrt((Precision::carre(particle[1]->getPosition().x-contactPointParticle_0.x))+(Precision::carre(particle[1]->getPosition().y-contactPointParticle_0.y))+(Precision::carre(particle[1]->getPosition().z-contactPointParticle_0.z)));

	//FAIRE ATTENTION AUX OBJETS STATIQUES, VOIR PDF cours page 20.21

	if (penetration != 0)//nous sommes face à une tige
	{
		if (distance > penetration)
		{
			double dif = distance - penetration;
			Vector3D direction = particle[0]->getPosition() - particle[1]->getPosition();
			direction.get_normalization();
			particle[0]->setPosition(particle[0]->getPosition() - direction * (dif / 2));
			particle[0]->setPosition(particle[1]->getPosition() + direction * (dif / 2));
		}
	}

	if (distance < particle[1]->getRadius())
	{
		//nos objets se touchent
		double tailleInterpenetration = particle[1]->getRadius() - distance;
		double masse_1 = particle[0]->getMass();
		double masse_2 = particle[1]->getMass();
		particle[0]->setPosition(normal* tailleInterpenetration * (masse_1 / (masse_1+masse_2)));
		particle[1]->setPosition(normal * -tailleInterpenetration * (masse_1 / (masse_1 + masse_2)));
		return tailleInterpenetration;
	}

	return distance;
};


