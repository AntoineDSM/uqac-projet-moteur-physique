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
		// D�tient la position lin�aire de la particule dans l'espace
		Vector3D position;

		// D�tient la v�locit� de la particule dans l'espace 
		Vector3D velocity;

		// D�tient l'acc�l�ration de la particule. Cette valeur peut �tre utilis�e pour d�finir l'acc�l�ration due � la gravit� (son utilisation principale), ou toute autre acc�l�ration constante

			Vector3D acceleration;

		// Maintient la force accumul�e � appliquer uniquement � l'it�ration de simulation suivante. Cette valeur est remise � z�ro � chaque �tape d'int�gration. 

		Vector3D forceAccum;

		// D�tient la quantit� d'amortissement appliqu�e au mouvement lin�aire *. L'amortissement est n�cessaire pour supprimer l'�nergie ajout�e par l'instabilit� num�rique de l'int�grateur
		double damping;

		// Il est plus utile de d�tenir l'inverse de la masse de la particule car l'int�gration est plus simple,
		// et parce qu'en simulation en temps r�el il est plus utile d'avoir des objets de masse infinie (inamovible) que de masse nulle (compl�tement instable en simulation num�rique)

			double inverseMass;


			// Int�gre la particule dans le temps selon la quantit� donn�e.
			// Cette fonction utilise une m�thode d'int�gration Newton-Euler, qui est une approximation lin�aire de l'int�grale correcte. Pour cette raison, elle peut �tre impr�cise dans certains cas. 

		void integrate(double duration);

		
	  



	public: 
		    // Efface les forces appliqu�es � la particule. Ceci sera appel� automatiquement apr�s chaque �tape d'int�gration.

		    void clearAccumulators();

			void setMass(const double mass) {};

			double getMass() const {};

			//v�rifier si la particule a une masse (masse >=0)
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



        // Efface les forces appliqu�es � la particule. Ceci sera appel� automatiquement apr�s chaque �tape d'int�gration.
		void clearAccumulator();
		// Ajoute la force donn�e � la particule pour �tre appliqu�e � la * prochaine it�ration seulement.
		void addForce(Vector3D& force);

	};
//}

//namespace Particle

#endif PARTICLE_HPP
