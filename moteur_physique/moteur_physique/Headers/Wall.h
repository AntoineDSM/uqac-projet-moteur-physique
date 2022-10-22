#pragma once

#include "Vector3D/Vector3D.h"
#include "Utils/Precision.h"
#include <vector>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

using namespace moteurJeux;
using namespace Precision;

class Wall
{

public:

	Vector3D* pointA;
	
	Vector3D* pointB;

	Vector3D* vecteurAB;

	std::vector<Vector3D*> listePointAB;

	Wall(Vector3D A, Vector3D B)
	{
		pointA = new Vector3D(A);
		pointB = new Vector3D(B);
		vecteurAB = new Vector3D(*pointB - *pointA);
		vecteurAB->get_normalization();
		fillListePoint();
	}

	inline void render()
	{
		glBegin(GL_LINES);
		glVertex3f(pointA->x, pointA->y, pointA->z); //point de d�part
		glVertex3f(pointB->x, pointB->y, pointB->z); //point d'arriv�
		glEnd();
	}

private:

	inline void fillListePoint()
	{
		double distance = std::sqrt((carre(pointB->x - pointA->x)) + (carre(pointB->y - pointA->y)) + (carre(pointB->z - pointA->z)));
		double pas = 0.01;
		double nombrePoints = distance / pas;

		int cpt = 0;
		while (cpt < nombrePoints)
		{
			Vector3D* nouveauPoint = (*pointA + *vecteurAB) + pas*cpt;
			listePointAB.push_back(nouveauPoint);
			cpt++;
		}
	}

};

