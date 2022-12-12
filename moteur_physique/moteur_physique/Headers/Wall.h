#pragma once

#ifndef WALL
#define WALL

#include "Vector3D/Vector3D.h"
#include "Utils/Precision.h"
#include <vector>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <Vector3D/Vector3D.h>

using namespace moteurJeux;
using namespace Precision;

class Wall
{

public:

	Vector3D* pointA;
	
	Vector3D* pointB;

	Vector3D* vecteurAB;

	Vector3D* planMur;

	std::vector<Vector3D*> listePointAB;

	Wall(Vector3D A, Vector3D B, Vector3D plan)
	{
		pointA = new Vector3D(A);
		pointB = new Vector3D(B);
		vecteurAB = new Vector3D(*pointB - *pointA);
		vecteurAB->get_normalization();
		planMur = new Vector3D(plan);
		fillListePoint();
	}

	inline void render()
	{
		glBegin(GL_LINES);
		glVertex3f(pointA->x, pointA->y, pointA->z); //point de départ
		glVertex3f(pointB->x, pointB->y, pointB->z); //point d'arrivé
		glEnd();
	}

private:

	inline void fillListePoint()
	{
		double distance = std::sqrt((carre(pointB->x - pointA->x)) + (carre(pointB->y - pointA->y)) + (carre(pointB->z - pointA->z)));
		double pas = 0.1;
		double nombrePoints = distance / pas;

		int cpt = 0;
		while (cpt < nombrePoints)
		{
			Vector3D direction = moteurJeux::Vector3D::get_normalization(*vecteurAB);
			Vector3D* nouveauPoint = new Vector3D(*pointA);
			if (direction.x != 0)
			{
				nouveauPoint->x =  direction.x + pas * cpt;
			}
			if (direction.y != 0)
			{
				nouveauPoint->y = direction.y + pas * cpt;
			}
			if (direction.z != 0)
			{
				nouveauPoint->z = direction.z + pas * cpt;
			}
			listePointAB.push_back(nouveauPoint);
			cpt++;
		}
	}

};

#endif WALL
