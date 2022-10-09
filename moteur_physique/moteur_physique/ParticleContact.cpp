

#include "ParticleContact.h"
#include "Particle.h"
#include "Vecteur3D.h"

using namespace moteurJeux;


Particle* particle[2];

//tentative d'implémenation de la formule 7.3

float sv = calculatingSeparatingVelocity();
// je met e à 1 pour l'instant
float e = 1;
float restitution = -e*sv;

//tentative de calcul de la conservation de la quantité de mouvement
float cqm = particle[0]->getMass()*particle[0]->getPosition() + particle[1]->getMass() * particle[1]->getPosition();




// tentative de calcul de l'impulsion
double totalInverseMass = particle[0]->getInverseMass() + particle[1]->getInverseMass();
double impulsion = sv / totalInverseMass;


float calculatingSeparatingVelocity() {

	//tentative d'implémenation de la formule 7.2
	
	float vs;
	Vector3D v1 = particle[0]->getPosition().operator-(particle[1]->getPosition());
	Vector3D v2 = particle[0]->getPosition().operator-(particle[1]->getPosition());
	Vector3D n = get_normalization(v2);
	vs=(float)v1.getScalar(n);
	
	return vs;
};

void resolve(float duration) {

//
};

void resolveVelocity() {

//
};

void resolveInterpretation() {

};


