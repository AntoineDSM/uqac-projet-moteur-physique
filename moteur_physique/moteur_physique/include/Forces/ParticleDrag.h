#pragma once
#include "Vector3D/Vector3D.h"
#include "Forces/ParticleForceGenerator.h"

using namespace moteurJeux;

class ParticleDrag : public ParticleForceGenerator
{
<<<<<<< HEAD
	private :
	
		//Coefficients de tra�n�e
		double m_k1;
		double m_k2;
	
	public:
	
		// Cr�e le g�n�rateur avec les coefficients donn�s. 	
		ParticleDrag(double m_k1, double m_k2);
	
	    // Applique une tra�n�e simplifi�e bas�e sur la v�locit� de la particule
		void updateForce(Particle* particle, float duration);
=======
private :
	//Coefficients de tra�n�e
	float m_k1;
	float m_k2;

public:

	// Cr�e le g�n�rateur avec les coefficients donn�s. 
		
		ParticleDrag(float m_k1, float m_k2);

    // Applique une tra�n�e simplifi�e bas�e sur la v�locit� de la particule
	void updateForce(Particle* particle, float duration);
>>>>>>> origin/Victor
};

