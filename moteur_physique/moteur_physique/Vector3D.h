//Date de création :
//Créer par :
//Date de dernière modification :
//Modifié par : 


#pragma once
#include <math.h>
#include <iostream>

#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

namespace moteurJeux {

//Our 3D vector just contain 3 coordinates. A lot of method can be usefull, get magnitude, normalize it, get his angle with the origin
class Vector3D
	{

	//attributes
	public:
		
		double x;
		double y;
		double z;

	//constructors
	public:

		//default constructor that creates a (0,0,0) Vector3D
		Vector3D() : x(0), y(0), z(0) 
		{
			//nothing more to be had here
		}

		//constructors with parameters to create a new one
		Vector3D(const double xCoord, const double yCoord, const double zCoord) : x(xCoord), y(yCoord), z(zCoord) 
		{
			//nothing more to be had here
		}

	//methods
	public :

		//---------------------------------------------------------DISPLAY OUR VECTOR---------------------------------------------------------
		inline void display() {
			std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
		}

		//---------------------------------------------------------NORMALIZATION---------------------------------------------------------

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

		//get the normalized vector of a given Vecteur3D
		inline static Vector3D get_normalization(Vector3D& vect)
		{
			if (get_magnitude(vect) > 1)
			{
				return vect *= ((double)1) / get_magnitude(vect);
			}
			else
				return vect;
		}

		//---------------------------------------------------------MAGNITUDE---------------------------------------------------------

		//get the norm of a vector means to calculate his lenght, get the magnitude of this vector
		inline double get_magnitude() { return sqrt(x * x + y * y + z * z);}

		//get the norm of a vector Vecteur3D
		inline static double get_magnitude(Vector3D& vect) { return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);}

		//---------------------------------------------------------ADDITION AND MULTIPLICATION BY SCALAR VALUE---------------------------------------------------------

		//add a to our Vecteur3D another one that is multiplied by a scalar
		void addMultipliedVector(Vector3D& vect, double facteur);
		
		// Adds the given vector to this, scaled by the given amount.
		void addScaledVector(const Vector3D& vector, double scale);

		//multiply our Vecteur3D with another one
		Vector3D multiplyBy(Vector3D& vect);

		//---------------------------------------------------------VECTORIAL PRODUCT---------------------------------------------------------

		//get the vectorial product between our vector and another one (axb means to obtain a vector orthogonal with a and b)
		Vector3D vectorialProduct(Vector3D& vect);

		//get vectorial product between 2 specified vectors
		static Vector3D vectorialProduct(Vector3D& vect1, Vector3D& vect2);
		
		//---------------------------------------------------------SCALAR PRODUCT---------------------------------------------------------

		//get the scalar product between our vector and another one (a.b means the size of b projected on a)
		double scalarProduct(Vector3D& vect);
		
		//---------------------------------------------------------CREATE AN ORTHONOMAL BASIS---------------------------------------------------------

		struct orthonormalBasis //9 points int the basis, 3 for vect(x), 3 for vect(y), 3 for vect(z)
		{
			double basis[9];
		};

		static bool isNULL(Vector3D& vect1);

		//---------------------------------------------------------OPERATORS ON VECTEUR3D---------------------------------------------------------

		Vector3D operator*(double value)
		{
			return Vector3D(x * value, y * value, z * value);
		}

		Vector3D operator*=(Vector3D& vect)
		{
			return Vector3D(x * vect.x, y * vect.y, z * vect.z);
		}

		//be able to multiplied our Vecteur3D with a scalar value (double value here) //void operator*=(double value)
		//Vector3D operator*=(double value)
		//{
		//	x * value;
		//	y * value;
		//	z * value;
		//}

		//return a copy of a Vecteur3D of a multiplication between a scalar value (double value here) and our Vecteur3D
		Vector3D operator*=(double value) const //avoid our object to be modified
		{
			return Vector3D(x * value, y * value, z * value);
		}

		void operator+(Vector3D& v) //get "v" attribute by the memory reference
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		//be able to add a Vecteur3D to our Vecteur3D
		void operator+=(Vector3D& v) //get "v" attribute by the memory reference
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		//return a copy of a Vecteur3D of an addition between a Vecteur3D added to our Vecteur3D
		Vector3D operator+=(Vector3D& v) const 
		{
			return Vector3D(x + v.x, y + v.y, z + v.z);
		}

		//be able to substract a Vecteur3D to our Vecteur3D
		void operator-=(Vector3D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		//return a copy of a Vecteur3D of an substraction between a Vecteur3D substracted to our Vecteur3D
		Vector3D operator-=(Vector3D& v) const
		{
			return Vector3D(x - v.x, y - v.y, z - v.z);
		}

	};

} //namespace moteurJeux

#endif VECTOR3D_HPP


