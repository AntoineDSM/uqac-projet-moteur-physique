#pragma one

#include "ParticleConctactGenerator.h"
#include "Utils/timing.h"

class WallContactGenerator : public ParticleContactGenerator
{
	
public :
	bool EstAuRepos(Particle p, TimingData t);
};