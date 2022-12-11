#pragma once

#include <ostream>
#include <vector>

#include "Cube.h"
#include "Rotations/RigidBody.h"
#include "Transform.h"
#include "ShapeRenderer.h"
#include "Boite.h"
#include "OctreeDetection.h"

class DemoRigidBodiesCollision
{

private:

	std::vector<RigidBody*> listeRigidBody = std::vector<RigidBody*>();
	std::vector<ShapeRenderer*> listeShapeRenderer = std::vector<ShapeRenderer*>();
	bool followCube = false;


public:

	GLFWwindow* window;
	Camera camera;

	DemoRigidBodiesCollision(GLFWwindow* newWindow, Camera newCamera, bool follow)
	{
		window = newWindow;
		camera = newCamera;
		followCube = follow;
		Init();
	}

	void Init()
	{
		std::cout << "Creation des RigidBodies" << std::endl;

		std::vector<Vector3D> listePositions{};//inserer des positions pour les tests
		std::vector<Vector3D> listeVelocites{};//inserer des velocites pour les tests
		//std::vector<Vector3D> listeLocalPointCoords = ;
		//std::vector<Vector3D> listeForces = ;

		for (int i = 0; i < 5; i++)
		{
			RigidBody* rb = CreerCube(listePositions[i], listeVelocites[i],i);
			listeRigidBody.push_back(rb);
			ShapeRenderer* shapeRenderer = new ShapeRenderer(rb);
			listeShapeRenderer.push_back(shapeRenderer);
		}

		//Creer un plan ou plusieurs

		//Creer contact resolution

		//Mettre camera a un emplacement plus generique (vu de coté du plan)
		camera.Position = glm::vec3(5, 5, 10);
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

			float distanceFarthest = 0;

			for (size_t i = 0; i < listeRigidBody.size(); i++)
			{
				float dist = listeRigidBody[i]->transform->getPosition().getMax();
				if (dist > distanceFarthest) distanceFarthest = dist;
				RigidBody* rigidbody = listeRigidBody[i];
				//ForceGenerator* forceGenerator = entities[i]->getComponent<ForceGenerator>();
				if (rigidbody != nullptr)
				{
					//if (forceGenerator != nullptr) forceGenerator->UpdateForce(rigidbody, 0.1f);
					rigidbody->Integrate(newDuration);
				}
			}

			//COLLISIONS
			std::vector<OctreeDetection*> octreeObjects;
			for (size_t i = 0; i < listeRigidBody.size(); i++)
			{
				if (!listeRigidBody[i]->primitive) continue;
				OctreeDetection* octreeObject = new OctreeDetection(listeRigidBody[i]);
				octreeObjects.push_back(octreeObject);
			}
			if (octreeObjects.size() == 0) return;
			OctreeNode* entryNode = new OctreeNode();
			entryNode = entryNode->BuildOctree(Vector3D(0, 0, 0), distanceFarthest, 2); //on prend une profondeur totalement arbitraire
			for (int i = 0; i < octreeObjects.size(); i++) {
				entryNode->InsertObject(octreeObjects[i]);
			}

			CollisionData* data;
			data->contactLeft = 50;
			entryNode->TestAllCollisions(data);

			if (data->contactLeft < 50) {
				for (int i = 0; i < 50 - data->contactLeft; i++) {
					data->contacts[i]->printInfoContact();
					exit(0);
				}
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

	RigidBody* CreerCube(Vector3D cubePosition, Vector3D cubeVelocity, int index)
	{
		Transform* transform = new Transform("RigidBodyCube : " + index);
		transform->setPosition(cubePosition);

		Boite* boite = new Boite(); //bien sur, si nous voulons un autre type de primitive, nous pouvons faire un enum et rentrer en parametre ce que nous souhaitons pour avoir Boite/Plan/Sphere

		RigidBody* rb = new RigidBody(transform, cubeVelocity);
		rb->SetPrimitiveBoite(boite);
		rb->Initialize(1, 0.9, 0.9, CubeBis(1, Vector3D(1, 1, 1)));
	}

	Matrix33 CubeBis(float m, Vector3D d)
	{
		float values[] =
		{
			1 / 12.0f * m * (d.y * d.y + d.z * d.z), 0,0,
			0, 1 / 12.0f * m * (d.x * d.x + d.z * d.z), 0,
			0, 0, 1 / 12.0f * m * (d.y * d.y + d.x * d.x)
		};
		return Matrix33(values);
	}

	/*
	Matrix33 SphereBis(float m, Vector3D d)
	{
		float values[] =
		{
			1 / 12.0f * m * (d.y * d.y + d.z * d.z), 0,0,
			0, 1 / 12.0f * m * (d.x * d.x + d.z * d.z), 0,
			0, 0, 1 / 12.0f * m * (d.y * d.y + d.x * d.x)
		};
		return Matrix33(values);
	}
	*/
};

