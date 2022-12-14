#pragma once

#ifndef TRANSFORM
#define TRANSFORM

#include "Rotations/Quaternion.h"

//-------------------------------------------------------------------CLASSE TRANSFORM-------------------------------------------------------------

//Garde les informations relatives � un rigidBody mais pourrait servir dans d'autre utilisation et d'autres types d'�l�ments.
class Transform
{

	private:
	
		Vector3D position = Vector3D();
		Vector3D rotation = Vector3D();
		Vector3D scale = Vector3D(1,1,1);
		std::string name;
	
	public:
		
		//Constructeur
		Transform(std::string name, Vector3D scale = Vector3D(1,1,1));
		
		//--------------------GETTER & SETTER------------------------

		void setPosition(Vector3D position);

		Vector3D getPosition();

		void setRotation(Vector3D rotation);

		Vector3D getRotation();
	
		Vector3D getScale();

		std::string getName();
};

#endif TRANSFORM