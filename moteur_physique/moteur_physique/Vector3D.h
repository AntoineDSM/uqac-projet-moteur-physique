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

		//DISPLAY OUR VECTOR
		void display() {
			std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
		}

		//NORMALIZATION

		//normalize a vector means to obtain his coordinates between 0 and 1, in the unit circle. We normalize only if the actual Vector3D is not in the unit circle.
		/*
		* if it's in the unit circle, that means the magnitude (the lenght) is < 1. So we need to verify the magnitude before normalizing it.
		* if it's not, it means that the max value of the vector is equal to the magnitude (ex : magnitude of 4 -> sqrt(0*0 + 4*4 + 0*0) = 4). So we need to divide by magnitude 
		* each parameter to fit them between 0 and 1.
		*/
		void get_normalization()
		{
			if (get_magnitude() > 1)
			{
				//x = x / get_magnitude();
				//y = y / get_magnitude();
				//z = z / get_magnitude();
				(*this) *= ((double)1) / get_magnitude();
			}
		}

		//get the normalized vector of a given Vecteur3D
		Vector3D get_normalization(Vector3D& vect)
		{
			if (get_magnitude(vect) > 1)
			{
				return vect *= ((double)1) / get_magnitude(vect);
			}
		}

		//MAGNITUDE

		//get the norm of a vector means to calculate his lenght, get the magnitude of this vector
		double get_magnitude()
		{
			return sqrt(x * x + y * y + z * z);
		}


		//get the norm of a vector Vecteur3D
		double get_magnitude(Vector3D& vect)
		{
			return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
 		}

		//ADDITION AND MULTIPLICATION BY SCALAR VALUE

		//add a to our Vecteur3D another one that is multiplied by a scalar
		void addMultipliedVector(Vector3D& vect, double facteur)
		{
			Vector3D multiplied = vect * facteur;
			(*this) += multiplied;
		}

		//multiply our Vecteur3D with another one
		Vector3D multiplyBy(Vector3D& vect)
		{
			return (*this) *= vect;
		}

		//VECTORIAL PRODUCT

		//get the vectorial product between our vector and another one (axb means to obtain a vector orthogonal with a and b)
		Vector3D vectorialProduct(Vector3D& vect)
		{
			return Vector3D(y*vect.z - z*vect.y, z*vect.x - x*vect.z, x*vect.y - y*vect.x);
		}

		//get vectorial product between 2 specified vectors
		Vector3D vectorialProduct(Vector3D& vect1, Vector3D& vect2)
		{
			return Vector3D(vect1.y * vect2.z - vect1.z * vect2.y, vect1.z * vect2.x - vect1.x * vect2.z, vect1.x * vect2.y - vect1.y * vect2.x);
		}
		
		//SCALAR PRODUCT

		//get the scalar product between our vector and another one (a.b means the size of b projected on a)
		double scalarProduct(Vector3D& vect)
		{
			return x * vect.x + y * vect.y + z * vect.z;
		}
		
		//CREATE AN ORTHONOMAL BASIS

		struct orthonormalBasis //9 points int the basis, 3 for vect(x), 3 for vect(y), 3 for vect(z)
		{
			double basis[9];
		};

		//return an orthonormal basis, 3 vectors.
		orthonormalBasis createOrthonormalBasis(Vector3D& vect1, Vector3D& vect2)
		{
			vect1 = get_normalization(vect1);
			vect2 = get_normalization(vect2);
			Vector3D vect3 = vectorialProduct(vect1,vect2);
			if (isNULL(vect3))
			{
				vect2 = vectorialProduct(vect1, vect3);
				orthonormalBasis myBase;
				double list[9] = { vect1.x, vect1.y, vect1.z, vect2.x, vect2.y, vect2.z, vect3.x, vect3.y, vect3.z };
				memcpy(myBase.basis, list, sizeof(list));
				return myBase;
			}

		}


		bool isNULL(Vector3D& vect1)
		{
			if (vect1.x == 0)
				if (vect1.y == 0)
					if (vect1.z == 0)
						return true;
			return false;
		}

		//OPERATORS ON VECTEUR3D

		Vector3D operator*(double value)
		{
			x * value;
			y * value;
			z * value;
		}

		Vector3D operator*=(Vector3D& vect)
		{
			x * vect.x;
			y * vect.y;
			z * vect.z;
		}

		//be able to multiplied our Vecteur3D with a scalar value (double value here) //void operator*=(double value)
		Vector3D operator*=(double value)
		{
			x * value;
			y * value;
			z * value;
		}

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


