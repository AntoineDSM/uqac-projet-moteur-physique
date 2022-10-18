//Date de création :
//Créer par :
//Date de dernière modification :
//Modifié par : 


#pragma once
#include <math.h>
#include <iostream>
#include <xmemory>
#include <memory>

#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

namespace moteurJeux {

//Notre objet Vector3D contient 3 coordonnees, X,Y et Z. Permet de modeliser des positions, des vitesses, des accelarations....
class Vector3D
	{

	//---------------------------------------------------------------------ATTRIBUTES--------------------------------------------------------------------------

	//Les coordonnees de notre vecteur.
	public:
		
		double x;
		double y;
		double z;

	//------------------------------------------------------------------CONSTRUCTEURS---------------------------------------------------------------------------
	
	public:

		//Constructeur par defaut.
		Vector3D() : x(0), y(0), z(0) 
		{
			//nothing more to be had here
		}

		//Constructeur avec initialisation
		Vector3D(const double xCoord, const double yCoord, const double zCoord) : 
			x(xCoord)
			, y(yCoord)
			, z(zCoord) 
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

		//Obtenir la normalisation de notre vecteur. (dans le cercle unite 0-1)
		inline static Vector3D get_normalization(Vector3D& vect)
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

		//-----------------------------------------------------------ADDITION AND MULTIPLICATION BY SCALAR VALUE---------------------------------------------------------

		//ajouter un vecteur multiplie par un facteur a notre vecteur.
		void addMultipliedVector(Vector3D& vect, double facteur);
		
		//meme methode que precedemment avec implementation differente.
		void addScaledVector(const Vector3D& vector, double scale);

		//multiplication entre notre vecteur et un second.
		Vector3D multiplyBy(Vector3D& vect);

		//------------------------------------------------------------------------VECTORIAL PRODUCT-----------------------------------------------------------------

		//obtenir le produit vectoriel entre notre vecteur et un second. a X b veut dire obtenir un troisieme vecteur orthogonal de a et b
		Vector3D vectorialProduct(Vector3D& vect);

		//avoir le produit vectoriel entre deux vecteur donnes.
		inline static Vector3D vectorialProduct(Vector3D& vect1, Vector3D& vect2)
		{
			return Vector3D(vect1.y * vect2.z - vect1.z * vect2.y, vect1.z * vect2.x - vect1.x * vect2.z, vect1.x * vect2.y - vect1.y * vect2.x);
		}
		
		//-------------------------------------------------------------------------SCALAR PRODUCT-------------------------------------------------------------------

		//avoir le produit scalaire entre notre vecteur et un second, le produit scalaire de a.b veut dire obtenir la longueur de b projete sur a.
		double scalarProduct(Vector3D& vect);
		
		//--------------------------------------------------------------------CREATE AN ORTHONOMAL BASIS-------------------------------------------------------------

		struct orthonormalBasis //9 points dans la base, basis[0-2] vecteur1, basis[3-5] vecteur2, basis[6-8] vecteur3.
		{
			double basis[8];
		};

		//savoir si un vecteur est un vecteur null, soit (0,0,0).
		inline static bool isNULL(Vector3D& vect1)
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


		//---------------------------------------------------------------------OPERATORS ON VECTEUR3D-----------------------------------------------------------------

		//permettre de multiplier notre vecteur avec un scalaire, un facteur.
		Vector3D operator*(double value)
		{
			return Vector3D(x * value, y * value, z * value);
		}

		//permettre de multiplier notre vecteur avec un scalaire, un facteur.
		Vector3D operator*=(double value)
		{
			return Vector3D(x * value, y * value, z * value);
		}

		//permettre de multiplier notre vecteur avec un second.
		Vector3D operator*=(Vector3D& vect)
		{
			return Vector3D(x * vect.x, y * vect.y, z * vect.z);
		}

		//permettre d'obtenir un vecteur correspondant a l'addition entre notre vecteur et un second.
		Vector3D operator+(Vector3D& v)
		{
			return Vector3D(x + v.x, y + v.y, z + v.z);
		}

		//ajouter un vecteur a notre vecteur.
		void operator+=(const Vector3D& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		//soustraire un vecteur a notre vecteur.
		void operator-=(Vector3D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		//avoir un vecteur correspondant a la soustraction entre notre vecteur et un second.
		Vector3D operator-(Vector3D& v)
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
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

#endif VECTOR3D_HPP


