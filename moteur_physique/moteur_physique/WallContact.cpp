#include "../include/Contacts/WallContactGenerator.h"


bool WallContactGenerator::EstAuRepos(Particle p, TimingData t) {

	Vector3D p1 = p.getAcceleration() * t.lastFrameDuration;
	Vector3D p2 = p.getVelocity();

	WallContactGenerator w;

	if (p1.x > p2.x && p1.y > p2.y && p1.z > p2.z)
	{
		
	}



	return true;
};
