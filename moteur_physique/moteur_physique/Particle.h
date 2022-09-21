//Date de cr�ation :
//Cr�er par : 
//Date de derni�re modification : 16/09/22
//Modifi� par : Victor GUIRAUD

#pragma once

#include "math.h"
#include "Vector3D.h"


#ifndef PARTICLE_HPP
#define PARTICLE_HPP

//namespace Particle {

	//Impl�menter la classe contenant les diff�rents types de particules (balles, boulets, laser...) et les comportements diff�rents de ces objets

	class Particle
	{

	protected:
		// Holds the linear position of the particle in * world space. 
		Vector3D position;

		// Holds the linear velocity of the particle in * world space. 
		Vector3D velocity;

		// Holds the acceleration of the particle. This value * can be used to set acceleration due to gravity (its primary use), or any other constant acceleration. 

			Vector3D acceleration;

		//Holds the accumulated force to be applied at the next simulation iteration only. This value is zeroed at each  integration step. 

		Vector3D forceAccum;

		// Holds the amount of damping applied to linear * motion. Damping is required to remove energy added through numerical instability in the integrator. 
		double damping;

		// Holds the inverse of the mass of the particle.It is more useful to hold the inverse mass because integration is simpler,
		// and because in real - time simulation it is more useful to have objects with infinite mass(immovable) than zero mass (completely unstable in numerical simulation).

			double inverseMass;

		



	    // Integrates the particle forward in time by the given amount.
		// This function uses a Newton-Euler integration method, which is a  linear approximation to the correct integral. For this reason it may be inaccurate in some cases. 
		void integrate(double duration);

		
	   // Clears the forces applied to the particle. This will be called automatically after each integration step.
	   
		void clearAccumulators();

			void setMass(const double mass) {};

			double getMass() const {};


			void setPosition(const Vector3D& position) {};

			void getPosition(Vector3D* position) const {};

			Vector3D getPosition() const {};

			void setPosition(const double x, const double y, const double z) {};


			void setVelocity(const Vector3D& position) {};

			void getVelocity(Vector3D* position) const {};

			void setVelocity(const double x, const double y, const double z) {};


			void setAcceleration(const Vector3D position){};

			void getAcceleration(Vector3D position) const {};

			void setAcceleration(const double x, const double y, const double z) {};

			void setDamping(const double damping) {};

			double getDamping() const {};


			//force de ressort
	/*
	Soit 2 particules P1 et P2 reli�es par un ressort
	d-> = P1-> - P2->
	Fr-> = -K(|d->|-l0)*d->/|d->|
	Si on veut faire �a � chaque frame il faut que P1 connaisse P2. Il faut donc r�fl�chir � comment caract�riser la force dans l'engine
	*/

			//flotabilit�
			/*
              objet immerg� d�s que y0-yw<-S 
			  y0 : centre objet
			  yw: coord liquide
			  S: profondeur
			  
			  Est ce que mon objet va frapper un fluid
*/



		// Clears the forces applied to the particle. This will be called automatically after each integration step.
		void clearAccumulator();

		/** * Adds the given force to the particle to be applied at the * next iteration only. */
		void addForce(Vector3D& force);

	};
//}

//namespace Particle

#endif PARTICLE_HPP
