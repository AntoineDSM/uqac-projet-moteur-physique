//Date de cr�ation :
//Cr�er par : 
//Date de derni�re modification : 16/09/22
//Modifi� par : Victor GUIRAUD

#pragma once

#include "math.h"
#include "Vector3D.h"


#ifndef PARTICLE_HPP
#define PARTICLE_HPP

using namespace moteurJeux;

//Impl�menter la classe contenant les diff�rents types de particules (balles, boulets, laser...) et les comportements diff�rents de ces objets
namespace moteurJeux {

	class Particle
	{
	public:

		//--------------------------------------------------------------CONSTRUCTEURS-----------------------------------------------------------------------------

		//Constructeur par defaut
		Particle() : position(), velocity(), acceleration(), damping(0), inverseMass(0), radius(0)
		{
		}

		//Constructeur avec initialisation
		Particle(Vector3D newPosition, Vector3D newVelocity, Vector3D newAcceleration, double newDamping, double newInverseMass, double radius) :
			position(newPosition)
			, velocity(newVelocity)
			, acceleration(newAcceleration)
			, damping(newDamping)
			, inverseMass(newInverseMass)
			, radius(radius)
		{
		}

		//Constructeur par copie.
		Particle(const Particle& p)
		{
			position = p.position;
			velocity = p.velocity;
			acceleration = p.acceleration;
			damping = p.damping;
			inverseMass = p.inverseMass;
			radius = p.radius;
		}

		//Destructeur
		~Particle()
		{
		}

	protected:

		//------------------------------------------------------------------ATTRIBUTS-----------------------------------------------------------------------------

		//Position de la particule dans l'espace, evolue en fonction du temps et de la vitesse.
		Vector3D position;

		//Vitesse actuelle de la particule, evolue en fonciton du temps et de l'acceleration. Est impacte par l'ammortissement (ex : frottements).
		Vector3D velocity;

		//Acceleration de la particule.
		Vector3D acceleration;

		//Facteur d'ammortissement.
		double damping;

		//FAIRE LE COMMENTAIRE
		double inverseMass;

		//Dans la partie 2, notre particule pourra etre impactee par de multiples forces exterieure, nous les concatenerons dans un seul vecteur3D qui agira sur l'acceleration.
		Vector3D forceAccum;

		//rayon de notre particule
		double radius;
		
	public:

		//----------------------------------------------------METHODS DEFINIES DANS LE .CPP-------------------------------------------------------------------

		//Permet de faire evoluer la position et la vitesse en fonction du temps. Permettra d'actualiser a chaque frame les valeurs.
		void integrate(double duration);


		//--------------------------------------------------MASS METHOD, GETTER & SETTER-----------------------------------------------------------------------

		//Setter de la masse, une masse ne peut etre egale a 0 pour eviter une erreur de division.
		inline void setMass(const double mass)
		{
			if (mass != 0)
			{
				inverseMass = 1.0f / mass;
			}
			else
				std::cout << "La masse voulue n'est pas possible car egale a 0. \n";
		}

		inline double getMass() const { return 1.0f / inverseMass; }

		inline void setInverseMass(const double inverseMassValue)
		{
			inverseMass = inverseMassValue;
		}

		inline double getInverseMass() { return inverseMass; }

		bool hasFiniteMass() const
		{
			return inverseMass >= 0.0f;
		}

		 inline double getRadius() { return radius; }

		//--------------------------------------------------POSITION METHODS, GETTER & SETTER------------------------------------------------------------------

		void getPosition(Vector3D* position) const;

		inline Vector3D getPosition() const { return position; }

		inline void setPosition(const Vector3D& newPosition)
		{
			position = newPosition;
		}

		inline void setPosition(const double x, const double y, const double z)
		{
			position.x = x;
			position.y = y;
			position.z = z;
		}

		//-------------------------------------------------------VELOCITY METHODS, GETTER & SETTER-------------------------------------------------------

		void getVelocity(Vector3D *position) const;

		inline Vector3D getVelocity() const { return velocity; }

		

		inline void setVelocity(const Vector3D& newVelocity)
		{
			velocity = newVelocity;
		}

		inline void setVelocity(const double x, const double y, const double z)
		{
			velocity.x = x;
			velocity.y = y;
			velocity.z = z;
		}

		//-------------------------------------------------------ACCELERATION METHODS, GETTER & SETTER--------------------------------------------------------------

		inline void setAcceleration(const Vector3D& newAcceleration)
		{
			acceleration = newAcceleration;
		}

		inline void setAcceleration(const double x, const double y, const double z)
		{
			acceleration.x = x;
			acceleration.y = y;
			acceleration.z = z;
		}

		inline Vector3D getAcceleration() { return acceleration; }

		//-------------------------------------------------------DAMPING METHODS, GETTER & SETTER-----------------------------------------------------------------

		inline void setDamping(const double dampingValue)
		{
			damping = dampingValue;
		}

		inline double getDamping() const { return damping; }

		//------------------------------------------------------METHOD FOR FORCE ACCUMULATOR, GETTER & SETTER-------------------------------------------------------

		//Notre accumulateur de force qui agira sur l'acceleration pourra etre reinitialise.
		void clearAccumulator();

		//Ajouter une force a cet accumulateur. 
		void addForce(const Vector3D& force);

	};
}//moteurJeux

#endif PARTICLE_HPP