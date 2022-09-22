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

	protected:
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


			// Intègre la particule dans le temps selon la quantité donnée.
			// Cette fonction utilise une méthode d'intégration Newton-Euler, qui est une approximation linéaire de l'intégrale correcte. Pour cette raison, elle peut être imprécise dans certains cas. 

		void integrate(double duration);

		
	  



	public: 
		    // Efface les forces appliquées à la particule. Ceci sera appelé automatiquement après chaque étape d'intégration.

		    void clearAccumulators();

			void setMass(const double mass) {};

			double getMass() const {};

			//vérifier si la particule a une masse (masse >=0)
			bool hasFiniteMass() const;


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



        // Efface les forces appliquées à la particule. Ceci sera appelé automatiquement après chaque étape d'intégration.
		void clearAccumulator();
		// Ajoute la force donnée à la particule pour être appliquée à la * prochaine itération seulement.
		void addForce(Vector3D& force);

	};
//}

//namespace Particle

#endif PARTICLE_HPP
