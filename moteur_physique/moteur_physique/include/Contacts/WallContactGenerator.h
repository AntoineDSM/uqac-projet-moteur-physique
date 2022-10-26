#pragma one

<<<<<<< HEAD
#include "ParticleContactGenerator.h"
#include "../Headers/Wall.h"
#include "..\ValuesReferences.h"
=======
#include "ParticleConctactGenerator.h"
#include "Forces/ParticleGravity.h"
#include "Utils/timing.h"
>>>>>>> Axel

using namespace valuesReferences;


class WallContactGenerator
{
<<<<<<< HEAD
public:

	Wall* wallElement;

	std::vector<Particle*> listeParticle = std::vector<Particle*>();

	float restitution;

	WallContactGenerator(std::vector<Particle*> _listeParticle, Wall* element, float restitution) : restitution(restitution), wallElement(element)
	{
		listeParticle = _listeParticle;
	}

	void resolveContact();

	void resolveVelocity(Particle* particle, Vector3D resultante);

	void resolvePenetration(Particle* particle, Vector3D resultante);
	Vector3D get_resultante(Particle* particle);
=======
	
public :

	bool EstAuRepos(Particle p, TimingData t);
	void repos(Particle p, ParticleGravity g);
>>>>>>> Axel
};