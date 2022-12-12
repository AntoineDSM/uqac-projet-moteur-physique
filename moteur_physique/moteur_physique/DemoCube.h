/*
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
	bool followCube = false;

	Vector3D cubePosition;
	Vector3D cubeVelocity;
	Vector3D localPointOnCube;
	Vector3D forceApplicated;


public :

	GLFWwindow* window;
	Camera camera;

	DemoCube(GLFWwindow* newWindow, Camera newCamera, bool follow, Vector3D position, Vector3D velocity, Vector3D localPointCoords, Vector3D force)
	{
		window = newWindow;
		camera = newCamera;
		followCube = follow;

		cubePosition = position;
		cubeVelocity = velocity;
		localPointOnCube = localPointCoords;
		forceApplicated = force;

		Init();
	}

	void Init()
	{
		std::cout << "Creation du rigidBody" << std::endl;

		Transform* transform = new Transform("RigidBodyCube");
		transform->setPosition(cubePosition);

		RigidBody* rb = new RigidBody(transform, cubeVelocity);
		rb->Initialize(1, 0.9, 0.9, CubeBis(1, Vector3D(1, 1, 1)));

		ShapeRenderer* shapeRenderer = new ShapeRenderer(rb);

		listeRigidBody.push_back(rb);
		listeShapeRenderer.push_back(shapeRenderer);

		camera.Position = glm::vec3(rb->GetPosition().x+5, rb->GetPosition().y, 10);

		std::cout << "Position : " << rb->GetPosition().x << "  " << rb->GetPosition().y << "  " << rb->GetPosition().z << std::endl;
		std::cout << "Orientation : w: " << rb->GetRotation().value[0] << " i: " << rb->GetRotation().value[1] << " j : " << rb->GetRotation().value[2] << " k : " << rb->GetRotation().value[3] << std::endl;

	}

	//Rafraichissement des valeurs de position et de vitesse a valeur de temps variable, nous actualisons a la duree prise par la derniere frame pour s'executer.
	void UpdateFixedFrameRate(bool pause, float duration)
	{
		if (duration < 500)
		{
			//La duree de la frame precedente va nous permettre de simuler la physique de n-1, nous ne savons pas le temps que cette frame va prendre pour effectuer sa boucle de jeu.
			//Nous prenons donc volontairement une unite de retard pour la simulation.
			float newDuration = duration * 0.00005;
			std::cout << "duration : " << newDuration << "\n";

			for (int i = 0; i < listeRigidBody.size(); i++)
			{
				listeRigidBody[i]->AddForceAtBodyPoint(forceApplicated, localPointOnCube);
				listeRigidBody[i]->Integrate(newDuration);
				
				if (followCube)//permettre a la camera de suivre le déplacement du cube
				{
					camera.Position = glm::vec3(listeRigidBody[i]->GetPosition().x, listeRigidBody[i]->GetPosition().y, listeRigidBody[i]->GetPosition().z + 3);
				}

				std::cout << "Position : " << listeRigidBody[i]->GetPosition().x << "  " << listeRigidBody[i]->GetPosition().y << "  " << listeRigidBody[i]->GetPosition().z << std::endl;
				std::cout << "Rotation : x : " << listeRigidBody[i]->transform->getRotation().x << " y : " << listeRigidBody[i]->transform->getRotation().y << " z : " << listeRigidBody[i]->transform->getRotation().z << std::endl;
				std::cout << "Orientation : w: " << listeRigidBody[i]->GetRotation().value[0] << " i : " << listeRigidBody[i]->GetRotation().value[1] << " j : " << listeRigidBody[i]->GetRotation().value[2] << " k : " << listeRigidBody[i]->GetRotation().value[3] << std::endl;
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
			1/12.0f * m * (d.y * d.y + d.z * d.z), 0,0,
			0, 1/12.0f * m * (d.x * d.x + d.z * d.z), 0,
			0, 0, 1/12.0f * m * (d.y * d.y + d.x * d.x)
		};
		return Matrix33(values);
	}
};

*/