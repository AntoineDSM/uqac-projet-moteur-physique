#pragma once

#include <ostream>

#include "Cube.h"
#include "Rotations/RigidBody.h"
#include "Transform.h"
#include "ShapeRenderer.h"

class DemoCube
{

private :

	std::vector<RigidBody*> listeRigidBody = std::vector<RigidBody*>();
	std::vector<ShapeRenderer*> listeShapeRenderer = std::vector<ShapeRenderer*>();


public :

	GLFWwindow* window;

	DemoCube()
	{
		Init();
	}

	void Init()
	{
		std::cout << "Creation du rigidBody" << std::endl;

		Transform* transform = new Transform("RigidBodyCube");
		transform->setPosition(Vector3D(0,0,0));

		RigidBody* rb = new RigidBody(transform, Vector3D (1,1,1));
		rb->Initialize(1, 0.9, 0.9, CubeBis(1, Vector3D(1, 1, 1)));

		ShapeRenderer* shapeRenderer = new ShapeRenderer(rb);

		std::cout << rb->GetPosition().x << "  " << rb->GetPosition().y << "  " << rb->GetPosition().z << std::endl;
			
		//rb->addComponent<GravityForceGenerator>();
		//rb->getComponent<GravityForceGenerator>()->Initialize(Vector3D(0, -0.05f, 0));
		Vector3D localPoint = Vector3D(0.1, 0.25, 0.15);
		rb->AddForceAtBodyPoint(Vector3D(0, 2, 0), localPoint);

		listeRigidBody.push_back(rb);
		listeShapeRenderer.push_back(shapeRenderer);
	}

	//Rafraichissement des valeurs de position et de vitesse a valeur de temps variable, nous actualisons a la duree prise par la derniere frame pour s'executer.
	void UpdateVariousFrameRate(bool pause, float duration)
	{
		if (pause)
		{
			//La duree de la frame precedente va nous permettre de simuler la physique de n-1, nous ne savons pas le temps que cette frame va prendre pour effectuer sa boucle de jeu.
			//Nous prenons donc volontairement une unite de retard pour la simulation.
			duration *= 0.0005;

			for (int i = 0; i < listeRigidBody.size(); i++)
			{
				listeRigidBody[i]->Integrate(duration);
				std::cout << listeRigidBody[i]->GetPosition().x << "  " << listeRigidBody[i]->GetPosition().y << "  " << listeRigidBody[i]->GetPosition().z << std::endl;
			}
		}
	}


	void DisplayOpenGL()
	{
		for (int i = 0; i < listeRigidBody.size(); i++)
		{
			drawSquare(listeRigidBody[i]->GetPosition().x, listeRigidBody[i]->GetPosition().y, 40);
		}
		for (int i = 0; i < listeShapeRenderer.size(); i++)
		{
			listeShapeRenderer[i]->render(window);
		}
	}

	void drawSquare(float cx, float cy, float d)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glBegin(GL_LINE_LOOP);
		glVertex2f((-d + cx) / (float)width, (-d + cy) / (float)height);//output vertex 
		glVertex2f((d + cx) / (float)width, (-d + cy) / (float)height);//output vertex 
		glVertex2f((d + cx) / (float)width, (d + cy) / (float)height);//output vertex 
		glVertex2f((-d + cx) / (float)width, (d + cy) / (float)height);//output vertex 
		glEnd();
	}

	Matrix33 CubeBis(float m, Vector3D d)
	{
		float values[] =
		{
			1 / 12.0f * m * (d.y * d.y + d.z * d.z), 0,0,
			0,1 / 12.0f * m * (d.x * d.x + d.z * d.z), 0,
			0,0,1 / 12.0f * m * (d.y * d.y + d.x * d.x)
		};
		return Matrix33(values);
	}
};

