//Date de création :
//Créer par : 
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#pragma once

#include "math.h"
#include "Vector3D.h"


#ifndef PARTICLE_HPP
#define PARTICLE_HPP

using namespace moteurJeux;

//Implémenter la classe contenant les différents types de particules (balles, boulets, laser...) et les comportements différents de ces objets
namespace moteurJeux {

	class Particle
	{

	protected:
		/*  Holds the linear position of the particle in * world space. */
		Vector3D position;

		/* Holds the linear velocity of the particle in * world space. */  /** * Holds the acceleration of the particle. This value * can be used to set acceleration due to gravity (its primary * use), or any other constant acceleration. */

		Vector3D velocity;

		/** * Holds the linear velocity of the particle in * world space. */  /** * Holds the acceleration of the particle. This value * can be used to set acceleration due to gravity (its primary * use), or any other constant acceleration. */

		Vector3D acceleration;

		/** * Holds the amount of damping applied to linear * motion. Damping is required to remove energy added * through numerical instability in the integrator. **/

		double damping;

		/*Holds the inverse of the mass of the particle.It* is more useful to hold the inverse mass because* integration is simpler, and because in real - time * simulation it is more useful to have objects with * infinite mass(immovable) than zero mass * (completely unstable in numerical simulation). */

		double inverseMass;

		/** * Integrates the particle forward in time by the given amount. * This function uses a Newton-Euler integration method, which is a * linear approximation to the correct integral. For this reason it * may be inaccurate in some cases. */

	    public :

		//----------------------------------------------------OTHER METHODS, NOT INLINE-------------------------------------------------------------------

		void integrate(double duration);

		/**
	   * Clears the forces applied to the particle. This will be
	   * called automatically after each integration step.
	   */
		void clearAccumulators();

		//--------------------------------------------------MASS METHOD-----------------------------------------------------------------------

		inline void setMass(const double mass)
		{
			if (mass != 0)
			{
				inverseMass = 1.0f / mass;
			}
			else
				std::cout << "Mass has not been setted, this inputed mass was equal to 0 \n";
		}

		inline double getMass() const { return 1.0f / inverseMass;}

		inline void setInverseMass(const double inverseMassValue)
		{
			inverseMass = inverseMassValue;
		}

		inline double getInverseMass() { return inverseMass;}

		//--------------------------------------------------POSITION METHODS------------------------------------------------------------------

		//void getPosition(Vector3D* position) const;

		inline Vector3D getPosition() const { return position;}

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

		//-------------------------------------------------------VELOCITY METHODS-------------------------------------------------------

		//void getVelocity(Vector3D *position) const;

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

		//-------------------------------------------------------ACCELERATION METHODS--------------------------------------------------------------

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

		inline Vector3D getAcceleration() { return acceleration;}

		//-------------------------------------------------------DAMPING METHODS-----------------------------------------------------------------

		inline void setDamping(const double dampingValue)
		{
			damping = dampingValue;
		}

		inline double getDamping() const { return damping; }

	};
}//moteurJeux

#endif PARTICLE_HPP
