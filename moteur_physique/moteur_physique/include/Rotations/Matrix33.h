#pragma once
#include "Vector3D/Vector3D.h"
#include "Rotations/Quaternion.h"
#include "vector"

//-------------------------------------------------------------------------------CLASSE MATRICE 3x3------------------------------------------------------------------------------------------
class Matrix33
{	

	public:

		//elle possède 9 valeurs
		float values[9];
	
		//----------------------------------------------------------------------CONSTRUCTEURS------------------------------------------------------------------------------------------------

		//constructeur par defaut
		Matrix33() = default;
	
		//constructeur avec passage de valeur
		Matrix33(float value[9])
		{
			for (int i = 0; i < 9; i++) {
				values[i] = value[i];
			}
		}

		//----------------------------------------------------------------------METHODES PUBLIQUES------------------------------------------------------------------------------------------------
	
		//Get determinant of our matrice
		static float GetDeterminant(const Matrix33& mat);
	
		// Get the Inverse matrix
		Matrix33 Inverse( );
	
		// Get the Transpose matrix
		Matrix33 Transpose();

		// Get the Transpose matrix
		Vector3D Transform(const Vector3D& vector);
	
		// Set the matrix base on a quaternion
		void SetOrientation(const Quaternion& q);

		//Multiplication par une seconde matrice
		Matrix33& const operator*=(const Matrix33& other);
		friend Matrix33 operator*(const Matrix33& premiereMatrice, const Matrix33& secondeMatrice);
		//Multiplication de l'ensemble par un vecteur
		Vector3D const operator*(const Vector3D& vector);
};