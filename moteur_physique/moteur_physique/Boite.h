#pragma once

#ifndef BOITE
#define BOITE

#include "Primitive.h"

class Boite : public Primitive
{

private :
	Vector3D halfSize;

	Vector3D vertices[8] =
	{
		Vector3D{-halfSize.x, -halfSize.y, -halfSize.z},
		Vector3D{-halfSize.x, -halfSize.y, +halfSize.z},
		Vector3D{-halfSize.x, +halfSize.y, -halfSize.z},
		Vector3D{-halfSize.x, +halfSize.y, +halfSize.z},
		Vector3D{+halfSize.x, -halfSize.y, -halfSize.z},
		Vector3D{+halfSize.x, -halfSize.y, +halfSize.z},
		Vector3D{+halfSize.x, +halfSize.y, -halfSize.z},
		Vector3D{+halfSize.x, +halfSize.y, +halfSize.z}
	};

public :

	//Constructeur
	Boite()
	{
		halfSize = Vector3D(0.5f, 0.5f, 0.5f);
		Vector3D _vertices[8] =
		{
			Vector3D{-halfSize.x, -halfSize.y, -halfSize.z},
			Vector3D{-halfSize.x, -halfSize.y, +halfSize.z},
			Vector3D{-halfSize.x, +halfSize.y, -halfSize.z},
			Vector3D{-halfSize.x, +halfSize.y, +halfSize.z},
			Vector3D{+halfSize.x, -halfSize.y, -halfSize.z},
			Vector3D{+halfSize.x, -halfSize.y, +halfSize.z},
			Vector3D{+halfSize.x, +halfSize.y, -halfSize.z},
			Vector3D{+halfSize.x, +halfSize.y, +halfSize.z}
		};
		for (int i = 0; i < 8; i++)
		{
			vertices[i] = _vertices[i];
		}
		m_offset = Matrix34();
		shape = "Boite";
	}

	void Initialize(Vector3D halfSize = Vector3D(0.5f, 0.5f, 0.5f), Matrix34 offset = Matrix34());

	//-----------------------------------------------------------GETTER & SETTER-------------------------------------------------------------------------------

	const Vector3D& getVertex(int i) const;
	
	Vector3D* getVertices() const;
	
	Vector3D getHalfSize() const;
	
	void setHalfSize(Vector3D halfSize);

	std::string getShape() const;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif BOITE