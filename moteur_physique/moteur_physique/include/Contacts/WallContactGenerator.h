#pragma once

#ifndef WALL_CONTACT_GENERATOR
#define WALL_CONTACT_GENERATOR

#include "ParticleContactGenerator.h"
#include "../Headers/Wall.h"
#include "..\ValuesReferences.h"
#include "ParticleConctactGenerator.h"
#include "Forces/ParticleGravity.h"
#include "Utils/timing.h"


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

	void resolveVelocity(Particle* particle, Vector3D resultante);

	void resolvePenetration(Particle* particle, Vector3D resultante);
	Vector3D get_resultante(Particle* particle);

};

#endif WALL_CONTACT_GENERATOR
