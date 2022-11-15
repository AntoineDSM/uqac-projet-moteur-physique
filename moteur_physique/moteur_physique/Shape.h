#pragma once

#include <vector>;
#include "Shader.h"
#include "Vecteur3D.h"

#include <GLFW/glfw3.h>

using namespace moteurJeux;

//----------------------------------------------------------------------CLASSE MERE PERMETTANT DE DESIGNER UNE FORME, cube/cercle....-----------------------------------------------------------------
class Shape
{
	protected:
	
		Vector3D position, rotation, scale;//informations relatives a notre forme
		unsigned int m_VBO;
		unsigned int m_VAO = -1;

	public:

		//-------------------------------GETTER & SETTER----------------------------------
	
		Shape(Vector3D _position, Vector3D _rotation, Vector3D _scale)
		{
			position = _position;
			rotation = _rotation;
			scale = _scale;
		}
	
		unsigned int getVAO()
		{
			return m_VAO;
		}
	
		Vector3D getPosition()
		{
			return position;
		}
	
		Vector3D getRotation()
		{
			return rotation;
		}
	
		Vector3D getScale()
		{
			return scale;
		}
	
};