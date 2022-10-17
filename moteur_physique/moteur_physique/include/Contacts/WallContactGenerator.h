#pragma one

#include "ParticleConctactGenerator.h"
#include "Forces/ParticleGravity.h"
#include "Utils/timing.h"

class WallContactGenerator : public ParticleContactGenerator
{
	
public :

	bool EstAuRepos(Particle p, TimingData t);
	void repos(Particle p, ParticleGravity g);
};