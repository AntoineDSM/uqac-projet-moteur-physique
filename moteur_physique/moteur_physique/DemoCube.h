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
	Camera camera;

	DemoCube(GLFWwindow* newWindow, Camera newCamera)
	{
		window = newWindow;
		camera = newCamera;

		Init();
	}

	void Init()
	{
		std::cout << "Creation du rigidBody" << std::endl;

		Transform* transform = new Transform("RigidBodyCube");
		transform->setPosition(Vector3D(-1,0,-1));

		RigidBody* rb = new RigidBody(transform, Vector3D (1,1,1));
		rb->Initialize(1, 0.9, 0.9, CubeBis(1, Vector3D(1, 1, 1)));

		ShapeRenderer* shapeRenderer = new ShapeRenderer(rb);

		std::cout << "Position : "<< rb->GetPosition().x << "  " << rb->GetPosition().y << "  " << rb->GetPosition().z << std::endl;
		std::cout << "Orientation : "<< rb->GetRotation().i << "  " << rb->GetRotation().j << "  " << rb->GetRotation().k << std::endl;
			
		Vector3D localPoint = Vector3D(0.1, 0.25, 0.15);
		rb->AddForceAtBodyPoint(Vector3D(1, 2, 0), localPoint);

		listeRigidBody.push_back(rb);
		listeShapeRenderer.push_back(shapeRenderer);

		camera.Position = glm::vec3(rb->GetPosition().x+1, rb->GetPosition().y+1, 3);
	}

	//Rafraichissement des valeurs de position et de vitesse a valeur de temps variable, nous actualisons a la duree prise par la derniere frame pour s'executer.
	void UpdateVariousFrameRate(bool pause, float duration)
	{
		if (pause && duration < 500)
		{
			//La duree de la frame precedente va nous permettre de simuler la physique de n-1, nous ne savons pas le temps que cette frame va prendre pour effectuer sa boucle de jeu.
			//Nous prenons donc volontairement une unite de retard pour la simulation.
			float newDuration = duration * 0.000005;
			std::cout << "duration : " << newDuration << "\n";

			for (int i = 0; i < listeRigidBody.size(); i++)
			{
				listeRigidBody[i]->Integrate(newDuration);
				//drawSquare(listeRigidBody[i]->GetPosition().x, listeRigidBody[i]->GetPosition().y, 40);
				std::cout << "Position : " << listeRigidBody[i]->GetPosition().x << "  " << listeRigidBody[i]->GetPosition().y << "  " << listeRigidBody[i]->GetPosition().z << std::endl;
				std::cout << "Orientation : " << listeRigidBody[i]->GetRotation().i << "  " << listeRigidBody[i]->GetRotation().j << "  " << listeRigidBody[i]->GetRotation().k << std::endl;
			}
		}
	}


	void DisplayOpenGL()
	{
		for (int i = 0; i < listeShapeRenderer.size(); i++)
		{
			listeShapeRenderer[i]->render(window, camera);
		}
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

