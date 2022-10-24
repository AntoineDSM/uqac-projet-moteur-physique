#pragma once
#include <math.h>
#include <iostream>
#include <xmemory>
#include <memory>

#ifndef VECTEUR3D_HPP
#define VECTEUR3D_HPP

namespace moteurJeux {

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
//Our 3D vector just contain 3 coordinates. A lot of method can be usefull, get magnitude, normalize it, get his angle with the origin
class Vecteur3D
========
//Notre objet Vector3D contient 3 coordonnees, X,Y et Z. Permet de modeliser des positions, des vitesses, des accelarations....
class Vector3D
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
	{

	//---------------------------------------------------------------------ATTRIBUTES--------------------------------------------------------------------------

	//Les coordonnees de notre vecteur.
	public:
		
		double x;
		double y;
		double z;

	//------------------------------------------------------------------CONSTRUCTEURS---------------------------------------------------------------------------
	
	public:

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//default constructor that creates a (0,0,0) Vector3D
		Vecteur3D() : x(0), y(0), z(0) 
========
		//Constructeur par defaut.
		Vector3D() : x(0), y(0), z(0) 
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			//nothing more to be had here
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//constructors with parameters to create a new one
		Vecteur3D(const double xCoord, const double yCoord, const double zCoord) : x(xCoord), y(yCoord), z(zCoord) 
========
		//Constructeur avec initialisation
		Vector3D(const double xCoord, const double yCoord, const double zCoord) : 
			x(xCoord)
			, y(yCoord)
			, z(zCoord) 
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
		}

		//Constructeur par copie
		Vector3D(const Vector3D& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
		}

		//Destructeur
		~Vector3D()
		{
		}

		//-----------------------------------------------------------------------METHODS-------------------------------------------------------------------------

	public :

		//------------------------------------------------------------------DISPLAY OUR VECTOR------------------------------------------------------------------------------
		
		inline void display(std::string indication) {
			std::cout << indication << "\n";
			std::cout << "(" << x << "," << y << "," << z << ")\n" << std::endl;
		}

		//--------------------------------------------------------------------NORMALIZATION--------------------------------------------------------------------------------

		//normalize a vector means to obtain his coordinates between 0 and 1, in the unit circle. We normalize only if the actual Vector3D is not in the unit circle.
		/*
		* if it's in the unit circle, that means the magnitude (the lenght) is < 1. So we need to verify the magnitude before normalizing it.
		* if it's not, it means that the max value of the vector is equal to the magnitude (ex : magnitude of 4 -> sqrt(0*0 + 4*4 + 0*0) = 4). So we need to divide by magnitude 
		* each parameter to fit them between 0 and 1.
		*/
		inline void get_normalization()
		{
			if (get_magnitude() > 1)
			{
				(*this) *= ((double)1) / get_magnitude();
			}
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//get the normalized vector of a given Vecteur3D
		Vecteur3D get_normalization(Vecteur3D& vect)
========
		//Obtenir la normalisation de notre vecteur. (dans le cercle unite 0-1)
		inline static Vector3D get_normalization(Vector3D& vect)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			if (get_magnitude(vect) > 1)
			{
				return vect *= ((double)1) / get_magnitude(vect);
			}
			else
				return vect;
		}

		//------------------------------------------------------------------------MAGNITUDE-------------------------------------------------------------------------

		//avoir la magnitude veut dire obtenir la longueur de ce vecteur par rapport a l'origine du repere (0,0,0)
		inline double get_magnitude() { return sqrt(x * x + y * y + z * z);}

		//avoir la magnitude d'un vecteur donne.
		inline static double get_magnitude(Vector3D& vect) { return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//get the norm of a vector Vecteur3D
		double get_magnitude(Vecteur3D& vect)
		{
			return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
 		}

		//ADDITION AND MULTIPLICATION BY SCALAR VALUE

		//add a to our Vecteur3D another one that is multiplied by a scalar
		void addMultipliedVector(Vecteur3D& vect, double facteur)
		{
			Vecteur3D multiplied = vect * facteur;
			(*this) += multiplied;
		}

		//multiply our Vecteur3D with another one
		Vecteur3D multiplyBy(Vecteur3D& vect)
		{
			return (*this) *= vect;
		}
========
		//-----------------------------------------------------------ADDITION AND MULTIPLICATION BY SCALAR VALUE---------------------------------------------------------

		//ajouter un vecteur multiplie par un facteur a notre vecteur.
		void addMultipliedVector(Vector3D& vect, double facteur);
		
		//meme methode que precedemment avec implementation differente.
		void addScaledVector(const Vector3D& vector, double scale);

		//multiplication entre notre vecteur et un second.
		Vector3D multiplyBy(Vector3D& vect);
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h

		//------------------------------------------------------------------------VECTORIAL PRODUCT-----------------------------------------------------------------

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//get the vectorial product between our vector and another one (axb means to obtain a vector orthogonal with a and b)
		Vecteur3D vectorialProduct(Vecteur3D& vect)
		{
			return Vecteur3D(y*vect.z - z*vect.y, z*vect.x - x*vect.z, x*vect.y - y*vect.x);
		}

		//get vectorial product between 2 specified vectors
		Vecteur3D vectorialProduct(Vecteur3D& vect1, Vecteur3D& vect2)
========
		//obtenir le produit vectoriel entre notre vecteur et un second. a X b veut dire obtenir un troisieme vecteur orthogonal de a et b
		Vector3D vectorialProduct(Vector3D& vect);

		//avoir le produit vectoriel entre deux vecteur donnes.
		inline static Vector3D vectorialProduct(Vector3D& vect1, Vector3D& vect2)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			return Vecteur3D(vect1.y * vect2.z - vect1.z * vect2.y, vect1.z * vect2.x - vect1.x * vect2.z, vect1.x * vect2.y - vect1.y * vect2.x);
		}
		
		//-------------------------------------------------------------------------SCALAR PRODUCT-------------------------------------------------------------------

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//get the scalar product between our vector and another one (a.b means the size of b projected on a)
		double scalarProduct(Vecteur3D& vect)
		{
			return x * vect.x + y * vect.y + z * vect.z;
		}
========
		//avoir le produit scalaire entre notre vecteur et un second, le produit scalaire de a.b veut dire obtenir la longueur de b projete sur a.
		double scalarProduct(Vector3D& vect);
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		
		//--------------------------------------------------------------------CREATE AN ORTHONOMAL BASIS-------------------------------------------------------------

		struct orthonormalBasis //9 points dans la base, basis[0-2] vecteur1, basis[3-5] vecteur2, basis[6-8] vecteur3.
		{
			double basis[8];
		};

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//return an orthonormal basis, 3 vectors.
		orthonormalBasis createOrthonormalBasis(Vecteur3D& vect1, Vecteur3D& vect2)
		{
			vect1 = get_normalization(vect1);
			vect2 = get_normalization(vect2);
			Vecteur3D vect3 = vectorialProduct(vect1,vect2);
			if (!isNULL(vect3))
			{
				vect2 = vectorialProduct(vect1, vect3);
				orthonormalBasis myBase;
				double list[9] = { vect1.x, vect1.y, vect1.z, vect2.x, vect2.y, vect2.z, vect3.x, vect3.y, vect3.z };
				memcpy(myBase.basis, list, sizeof(list));
				return myBase;
			}

		}


		bool isNULL(Vecteur3D& vect1)
========
		//savoir si un vecteur est un vecteur null, soit (0,0,0).
		inline static bool isNULL(Vector3D& vect1)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			if (vect1.x == 0)
				if (vect1.y == 0)
					if (vect1.z == 0)
						return true;
			return false;
		}

		//si nous voulons remettre a (0,0,0) notre vecteur.
		inline void clear()
		{
			x = 0;
			y = 0;
			z = 0;
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		Vecteur3D operator*(double value)
		{
			x * value;
			y * value;
			z * value;
		}

		Vecteur3D operator*=(Vecteur3D& vect)
		{
			x * vect.x;
			y * vect.y;
			z * vect.z;
		}

		//be able to multiplied our Vecteur3D with a scalar value (double value here) //void operator*=(double value)
		Vecteur3D operator*=(double value)
		{
			x * value;
			y * value;
			z * value;
		}

		//return a copy of a Vecteur3D of a multiplication between a scalar value (double value here) and our Vecteur3D
		Vecteur3D operator*=(double value) const //avoid our object to be modified
		{
			return Vecteur3D(x * value, y * value, z * value);
		}

		void operator+(Vecteur3D& v) //get "v" attribute by the memory reference
========

		//---------------------------------------------------------------------OPERATORS ON VECTEUR3D-----------------------------------------------------------------

		//permettre de multiplier notre vecteur avec un scalaire, un facteur.
		Vector3D operator*(double value)
		{
			return Vector3D(x * value, y * value, z * value);
		}

		//permettre de multiplier notre vecteur avec un scalaire, un facteur.
		Vector3D operator*=(double value)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			return Vector3D(x * value, y * value, z * value);
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//be able to add a Vecteur3D to our Vecteur3D
		void operator+=(Vecteur3D& v) //get "v" attribute by the memory reference
========
		//permettre de multiplier notre vecteur avec un second.
		Vector3D operator*=(Vector3D& vect)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			return Vector3D(x * vect.x, y * vect.y, z * vect.z);
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//return a copy of a Vecteur3D of an addition between a Vecteur3D added to our Vecteur3D
		Vecteur3D operator+=(Vecteur3D& v) const 
========
		//permettre d'obtenir un vecteur correspondant a l'addition entre notre vecteur et un second.
		Vector3D operator+(Vector3D& v)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			return Vecteur3D(x + v.x, y + v.y, z + v.z);
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//be able to substract a Vecteur3D to our Vecteur3D
		void operator-=(Vecteur3D& v)
========
		//ajouter un vecteur a notre vecteur.
		void operator+=(const Vector3D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		//soustraire un vecteur a notre vecteur.
		void operator-=(Vector3D& v)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

<<<<<<<< HEAD:moteur_physique/moteur_physique/Vecteur3D.h
		//return a copy of a Vecteur3D of an substraction between a Vecteur3D substracted to our Vecteur3D
		Vecteur3D operator-=(Vecteur3D& v) const
========
		//avoir un vecteur correspondant a la soustraction entre notre vecteur et un second.
		Vector3D operator-(Vector3D& v)
>>>>>>>> cf253e3455649aaa2f836fbfaa8967b2652d6e54:moteur_physique/moteur_physique/Vector3D.h
		{
			return Vecteur3D(x - v.x, y - v.y, z - v.z);
		}
		const Vector3D operator-(const Vector3D& v)
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}

		//permettre d'associer a notre vecteur les valeurs d'un autre vecteur.
		void operator=(Vector3D& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		void operator=(const Vector3D& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

	};

} //namespace moteurJeux

#endif VECTEUR3D_HPP


