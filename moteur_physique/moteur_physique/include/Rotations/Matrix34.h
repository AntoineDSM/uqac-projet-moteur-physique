#pragma once

#pragma once
#include "Vector3D/Vector3D.h"
#include "Rotations/Quaternion.h"
#include "Matrix33.h"

//-------------------------------------------------------------CLASSE MATRICE 3x4-------------------------------------------------------------------------------------
class Matrix34
{

	public:
	
		//elle contient 12 valeurs
		float values[12];
	
		//---------------------------------------------------------------CONSTRUCTEURS-------------------------------------------------------------------------------------
	
		//Constructeur de matrice 3x4 identit�
		Matrix34()
		{
			for (int i = 0; i < 12; i++) {
				if (i % 5 == 0) {
					values[i] = 1;
				}
				else {
					values[i] = 0;
				}
			}
			
		}
	
		//constructeur par recopie
		Matrix34(const Matrix34& other)
		{
			{
				for (int i = 0; i < 12; i++) {
					values[i] = other.values[i];
				}
			}
		}
	
		//Constructeur de reconstruction Matrice33 + vecteur
		Matrix34(const Matrix33& mat33, const Vector3D& vect)
		{
			values[0] = mat33.values[0];
			values[1] = mat33.values[1];
			values[2] = mat33.values[2];
			values[3] = vect.x;
			values[4] = mat33.values[4];
			values[5] = mat33.values[5];
			values[6] = mat33.values[6];
			values[7] = vect.y;
			values[8] = mat33.values[8];
			values[9] = mat33.values[9];
			values[10] = mat33.values[10];
			values[11] = vect.z;
		}
	
		//-----------------------------------------------------METHODES PUBLIQUES-------------------------------------------------------------------------------------
		
		// Get the Inverse matrix
		Matrix34 Inverse();

		// Set the matrix base on a quaternion and a position
		void SetOrientationAndPosition(const Quaternion& q, const Vector3D& p);

		// Get a 33 from this 34
		Matrix33 ToMatrix33() const;

		// Transform a position
		Vector3D TransformPosition(const Vector3D& vector);

		// Transform a direction by ignoring the translation
		Vector3D TransformDirection(const Vector3D& vector);

	
		//Multiplication par une seconde matrice
		Matrix34& const operator*=(const Matrix34& other);
		friend Matrix34 operator*(const Matrix34& premiereMatrice, const Matrix34& secondeMatrice);

		//Multiplication de l'ensemble par un vecteur
		Vector3D const operator* (const Vector3D& vector);
	
};