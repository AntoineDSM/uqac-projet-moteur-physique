#pragma once
#include <math.h>
#include <iostream>

#ifndef VECTEUR3D_HPP
#define VECTEUR3D_HPP

namespace moteurJeux {

//Our 3D vector just contain 3 coordinates. A lot of method can be usefull, get magnitude, normalize it, get his angle with the origin
class Vecteur3D
	{

	//attributes
	public:
		
		double x;
		double y;
		double z;

	//constructors
	public:

		//default constructor that creates a (0,0,0) Vector3D
		Vecteur3D() : x(0), y(0), z(0) 
		{
			//nothing more to be had here
		}

		//constructors with parameters to create a new one
		Vecteur3D(const double xCoord, const double yCoord, const double zCoord) : x(xCoord), y(yCoord), z(zCoord) 
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
		Vecteur3D get_normalization(Vecteur3D& vect)
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
		double get_magnitude(Vecteur3D& vect)
		{
			return sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
 		}

		//ajout d'un vecteur multiplié par un facteur (this += Vecteur3D*facteur)
		//ajout du produit entre deux Vecteur3D (x = x1*x2, y = y1*y2 , z = z1*z2)
		//ajout du produit vectoriel entre deux Vecteur3D (x = y1*z2 - z1*y2, y = z1*x2 - x1*z2, z = x1*y2 - y1*x2)
		//ajout du produit scalaire entre deux Vecteur3D (x1*x2 + y1*y2 + z1*z2) 
		//creation d'une base orthonormée avec deux Vecteur3D (a et b) car "a" vectoriel "b" donne "c", "c" normal à "a" et "b", "c" vectoriel "a" donne "d", "a","c" et "d" forment une base orthonormée.

		//OPERATORS ON VECTEUR3D

		//be able to multiplied our Vecteur3D with a scalar value (double value here) //void operator*=(double value)
		Vecteur3D operator*=(double value)
		{
			x* value;
			y* value;
			z* value;
		}

		//return a copy of a Vecteur3D of a multiplication between a scalar value (double value here) and our Vecteur3D
		Vecteur3D operator*=(double value) const //avoid our object to be modified
		{
			return Vecteur3D(x * value, y * value, z * value);
		}

		//be able to add a Vecteur3D to our Vecteur3D
		void operator+=(Vecteur3D& v) //get "v" attribute by the memory reference
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		//return a copy of a Vecteur3D of an addition between a Vecteur3D added to our Vecteur3D
		Vecteur3D operator+=(Vecteur3D& v) const 
		{
			return Vecteur3D(x + v.x, y + v.y, z + v.z);
		}

		//be able to substract a Vecteur3D to our Vecteur3D
		void operator-=(Vecteur3D& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		//return a copy of a Vecteur3D of an substraction between a Vecteur3D substracted to our Vecteur3D
		Vecteur3D operator-=(Vecteur3D& v) const
		{
			return Vecteur3D(x - v.x, y - v.y, z - v.z);
		}

	};

} //namespace moteurJeux

#endif VECTEUR3D_HPP


