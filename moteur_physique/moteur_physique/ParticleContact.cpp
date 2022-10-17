
#include "ParticleContact.h"
#include "Particle.h"
#include "Vector3D.h"

using namespace moteurJeux;

ParticleContact::ParticleContact(Particle* particles[2], float restitution, float penetration, Vector3D contactNormal) : restitution(restitution), penetration(penetration), contactNormal(contactNormal)
{
	particle[0] = particles[0];
	particle[1] = particles[1];
}

float ParticleContact::calculatingSeparatingVelocity()
{
	float vs;

	Vector3D velocity0 = particle[0]->getVelocity();
	Vector3D velocity1 = particle[1]->getVelocity();
	Vector3D velocity = velocity0.operator-(velocity1);
	//Vector3D velocity = particle[0]->getVelocity() - particle[1]->getVelocity();

	Vector3D position0 = particle[0]->getPosition();
	Vector3D position1 = particle[1]->getPosition();
	Vector3D position = position0.operator-(position1);

	//Vector3D position = particle[0]->getPosition() - particle[1]->getPosition();
	Vector3D normalizedVector = Vector3D::get_normalization(position);
	vs = velocity.scalarProduct(position);

	return vs;
};

void ParticleContact::resolve(float duration)// si nous resolvons les contacts ici, l'inversion de vitesse et l'ajustement de la position sont instantanés, la durée d'une frame n'a pas grand chose a faire la ? rien ne dépend du temps c'est une impulsion
{
	resolveInterpretation();
	resolveVelocity();
	//gestion des contacts au repos a peut etre besoin de duration, ajouter methode : resolveAtRestState(float duration) !!!!!!!!!!!!!
};

void ParticleContact::resolveVelocity(float e)
{
	float seperatingVelocity = calculatingSeparatingVelocity();

	if (e == 1)//parfaitement elastique
	{
		//seperatingVelocity reste la meme
	}
	else if (e == 0)//parfaitement inélastiqgue
	{
		seperatingVelocity = 0;
	}
	else if (e > 0 && e < 1)//elastique
	{
		seperatingVelocity *= e;
	}

	//difference de vitesse entre nos deux objets
	Vector3D velocity1 = particle[0]->getVelocity();
	Vector3D velocity2 = particle[1]->getVelocity();
    Vector3D velocity = velocity1.operator-(velocity2);
	//Vector3D velocity = particle[0]->getVelocity() - particle[1]->getVelocity();
	//calcul du vecteur normal à nos objets
	Vector3D normal = Vector3D::vectorialProduct(velocity1, velocity2);
	double d = ((double)e + 1) / (1 / particle[0]->getMass() + 1 / particle[1]->getMass());
	//calcul du facteur k, cf document cours.
	Vector3D velocity_d = velocity.operator*(d);
	double k = normal.scalarProduct(velocity_d);
;
	Vector3D v1 = (normal * k) * (1 / particle[0]->getMass()) * seperatingVelocity;
	Vector3D v2 = (normal * k) * (1 / particle[0]->getMass()) * seperatingVelocity;
	Vector3D newVelocity_1 = velocity1.operator-(v1);
	Vector3D newVelocity_2 = velocity2.operator-(v2);

	//Vector3D newVelocity_1 = particle[0]->getVelocity() - (normal * k) * (1 / particle[0]->getMass()) * seperatingVelocity;
	//Vector3D newVelocity_2 = particle[1]->getVelocity() - (normal * k) * (1 / particle[1]->getMass()) * seperatingVelocity;

	particle[0]->setVelocity(newVelocity_1);
	particle[1]->setVelocity(newVelocity_2);
};

void ParticleContact::resolveInterpretation()
{
	//vecteur normal entre nos deux objets
	Vector3D v1 = particle[0]->getVelocity();
	Vector3D v2 = particle[1]->getVelocity();
	Vector3D normal = Vector3D::vectorialProduct(v1, v2);

	//vecteur de direction entre les deux objets
	Vector3D position0 = particle[0]->getPosition();
	Vector3D position1 = particle[1]->getPosition();
	Vector3D vectorBetweenParticles = position0.operator-(position1);
	//Vector3D vectorBetweenParticles = particle[1]->getPosition() - particle[0]->getPosition();
	vectorBetweenParticles.get_normalization();

	//extreme de notre particle dans la direction de la seconde particule
	Vector3D vbp_radius = vectorBetweenParticles * particle[0]->getRadius();
	Vector3D contactPointParticle_0 = particle[0]->getPosition().operator+(vbp_radius);
	//distance entre cet extreme et le centre seconde particule
	double distance = std::sqrt((Precision::carre(particle[1]->getPosition().x - contactPointParticle_0.x)) + (Precision::carre(particle[1]->getPosition().y - contactPointParticle_0.y)) + (Precision::carre(particle[1]->getPosition().z - contactPointParticle_0.z)));


	//FAIRE ATTENTION AUX OBJETS STATIQUES, VOIR PDF cours page 20.21


	if (distance < particle[1]->getRadius())
	{
		//nos objets se touchent
		double tailleInterpenetration = particle[1]->getRadius() - distance;
		double masse_1 = particle[0]->getMass();
		double masse_2 = particle[1]->getMass();
		particle[0]->setPosition(normal * tailleInterpenetration * (masse_1 / (masse_1 + masse_2)));
		particle[1]->setPosition(normal * -tailleInterpenetration * (masse_1 / (masse_1 + masse_2)));
	}
};


