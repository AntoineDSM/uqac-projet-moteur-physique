#include "../include/Contacts/WallContactGenerator.h"


bool WallContactGenerator::EstAuRepos(Particle p, TimingData t) {

	Vector3D p1 = p.getAcceleration() * t.lastFrameDuration;
	Vector3D p2 = p.getVelocity();

	if (p1.x > p2.x && p1.y > p2.y && p1.z > p2.z)
	{
		return true;
	}
	return false;
};

void WallContactGenerator::repos(Particle p, ParticleGravity g) {
	Vector3D vecZero;
	vecZero.x, vecZero.y, vecZero.z = 0;

	//Nous voulon trouver la vélocité relative dans la direction de la normal
	Vector3D velocityRelative = p.getAcceleration() - p.getVelocity();


	//On recherche ici de savoir si cela est dû à la gravité
	if (velocityRelative == g) {
		//ignoré la vélocité dans les autres direction
		//TO DO
	}
	else {
		p.setVelocity(vecZero);
	}
	
};
