//Date de création :
//Créer par : 
//Date de dernière modification : 16/09/22
//Modifié par : Victor GUIRAUD

#pragma once

#include "math.h"
#include "Vector3D.h"


#ifndef PARTICLE_HPP
#define PARTICLE_HPP

//namespace Particle {

	//Implémenter la classe contenant les différents types de particules (balles, boulets, laser...) et les comportements différents de ces objets

	class Particle
	{

	public:
		// Détient la position linéaire de la particule dans l'espace
		Vector3D position;

		// Détient la vélocité de la particule dans l'espace 
		Vector3D velocity;

		// Détient l'accélération de la particule. Cette valeur peut être utilisée pour définir l'accélération due à la gravité (son utilisation principale), ou toute autre accélération constante

		Vector3D acceleration;

		// Maintient la force accumulée à appliquer uniquement à l'itération de simulation suivante. Cette valeur est remise à zéro à chaque étape d'intégration. 

		Vector3D forceAccum;

		// Détient la quantité d'amortissement appliquée au mouvement linéaire *. L'amortissement est nécessaire pour supprimer l'énergie ajoutée par l'instabilité numérique de l'intégrateur
		double damping;

		// Il est plus utile de détenir l'inverse de la masse de la particule car l'intégration est plus simple,
		// et parce qu'en simulation en temps réel il est plus utile d'avoir des objets de masse infinie (inamovible) que de masse nulle (complètement instable en simulation numérique)

		double inverseMass;


		
	  

		//----------------------------------------------------OTHER METHODS, NOT INLINE-------------------------------------------------------------------

	 
		// Intègre la particule dans le temps selon la quantité donnée.
		// Cette fonction utilise une méthode d'intégration Newton-Euler, qui est une approximation linéaire de l'intégrale correcte. Pour cette raison, elle peut être imprécise dans certains cas. 

		    void integrate(double duration);


		    // Efface les forces appliquées à la particule. Ceci sera appelé automatiquement après chaque étape d'intégration.

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

			inline double getMass() const { return 1.0f / inverseMass; }

			inline void setInverseMass(const double inverseMassValue)
			{
				inverseMass = inverseMassValue;
			}

			inline double getInverseMass() { return inverseMass; }


			//vérifier si la particule a une masse (masse >=0)
			bool hasFiniteMass() const;

			//--------------------------------------------------POSITION METHODS------------------------------------------------------------------

					//void getPosition(Vector3D* position) const;

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

			inline Vector3D getAcceleration() { return acceleration; }

			//-------------------------------------------------------DAMPING METHODS-----------------------------------------------------------------

			inline void setDamping(const double dampingValue)
			{
				damping = dampingValue;
			}

			inline double getDamping() const { return damping; }



			// Efface les forces appliquées à la particule. Ceci sera appelé automatiquement après chaque étape d'intégration.
			void clearAccumulator();
			// Ajoute la force donnée à la particule pour être appliquée à la * prochaine itération seulement.

			void addForce(Vector3D& force);


		



        
	};
//}

//namespace Particle

#endif PARTICLE_HPP


		//force de ressort
	/*
	Soit 2 particules P1 et P2 reliées par un ressort
	d-> = P1-> - P2->
	Fr-> = -K(|d->|-l0)*d->/|d->|
	Si on veut faire ça à chaque frame il faut que P1 connaisse P2. Il faut donc réfléchir à comment caractériser la force dans l'engine
	*/

	//flotabilité
	/*
	  objet immergé dès que y0-yw<-S
	  y0 : centre objet
	  yw: coord liquide
	  S: profondeur

	  Est ce que mon objet va frapper un fluid
*/