#pragma once

#include "Vecteur3D.h"
#include "Rotations/Quaternion.h"

//-------------------------------------------------------------------CLASSE TRANSFORM-------------------------------------------------------------

//Garde les informations relatives à un rigidBody mais pourrait servir dans d'autre utilisation et d'autres types d'éléments.
class Transform
{

	private:
	
		Vector3D position = Vector3D();
		Vector3D rotation = Vector3D();
		Vector3D scale = Vector3D(0.1,0.1,0.1);
		std::string name;
	
	public:
		
		//Constructeur
		Transform(std::string name);
		
		//--------------------GETTER & SETTER------------------------

		void setPosition(Vector3D position);

		Vector3D getPosition();

		void setRotation(Vector3D rotation);

		Vector3D getRotation();
	
		Vector3D getScale();
};

