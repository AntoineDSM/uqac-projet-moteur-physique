#pragma once
#include "Vector3D/Vector3D.h"

using namespace moteurJeux;

//------------------------------------------------CLASSE IMPLEMENTANT LES QUATERNIONS--------------------------------------------------------------------------

class Quaternion
{

	public:
	
		//w,i,j,k
		float value[4];
	
		//--------------------------------------------------CONSTRUCTEURS----------------------------------------------------------
		
		//quaternion de base
		float w, i, j, k;
		Quaternion() : w(1), i(0), j(0), k(0) {}
		//Constructeur par defaut
		//Quaternion() = default;
	
		//Constructeur par passage de parametres
		Quaternion(float w, float i, float j, float k)
		{
			value[0] = w;
			value[1] = i;
			value[2] = j;
			value[3] = k;
		}
		
		//Constructeur par recopie
		Quaternion(const Quaternion& other) : value{other.value[0], other.value[1], other.value[2], other.value[3]}
		{
			//rien a ajouter
		}


		//--------------------------------------------METHODES PUBLIQUES-----------------------------------------------------------
		
		//utilitaire
		Vector3D ToEuler();

		void SetByEulerRotation(Vector3D euler);

		// normalize by multipling the quaternion by the inverse of its magnitude
		void Normalized();

		// Rotate the quaternion by a vector -multiply this by q = (e, dx, dy, dz)
		void RotateByVector(const Vector3D& vector);

		// Apply the quaternion update by the angular velcity
		void UpdateByAngularVelocity(const Vector3D& rotation, float duration);

		// Quaternion multiplication
		Quaternion operator* (const Quaternion& other);
};