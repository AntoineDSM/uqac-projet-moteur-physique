#pragma once

#ifndef PARTICLE_DRAG
#define PARTICLE_DRAG

#include "Vector3D/Vector3D.h"
#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;

class ParticleDrag : public ParticleForceGenerator
{
	private :
	
		//Coefficients de tra�n�e
		double m_k1;
		double m_k2;
	
	public:
	
		// Cr�e le g�n�rateur avec les coefficients donn�s. 	
		ParticleDrag(double m_k1, double m_k2);
	
	    // Applique une tra�n�e simplifi�e bas�e sur la v�locit� de la particule
		void updateForce(Particle* particle, float duration);
};

#endif PARTICLE_DRAG
