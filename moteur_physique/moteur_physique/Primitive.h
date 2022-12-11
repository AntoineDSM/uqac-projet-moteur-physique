#pragma once

#ifndef PRIMITIVE
#define PRIMITIVE

#include "Rotations/Matrix34.h"

class Primitive
{

protected:
		std::string shape;
		Matrix34 m_offset = Matrix34();

public :

	Primitive()
	{
		//Rien a ajouter
	}

	//Constructeur
	Primitive(Matrix34 _offset)
	{
		m_offset = _offset;
	}

	//-----------------------------------------------------------GETTER & SETTER-------------------------------------------------------------------------------
	
	const Matrix34 getOffset() const;

	void setOffset(Matrix34 _offset);

	//Permet de recuperer la forme de notre primitive, utile pour la gestion des collisions et des comportements differents entre les types d'objets
	std::string getShape() const;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif PRIMITIVE