#pragma one

#include "ParticleConctactGenerator.h"
#include "../Headers/Wall.h"
#include "..\ValuesReferences.h"

using namespace valuesReferences;


class WallContactGenerator
{
public:

	Wall* wallElement;

	std::vector<Particle*> listeParticle = std::vector<Particle*>();

	float restitution;

	WallContactGenerator(std::vector<Particle*> _listeParticle, Wall* element, float restitution) : restitution(restitution), wallElement(element)
	{
		listeParticle = _listeParticle;
	}

	void resolveContact();

	void resolveVelocity(Particle* particle, Vector3D* pointContact);

	void resolvePenetration(Particle* particle, Vector3D* pointContact);
};