#pragma once

#ifndef DEMO_RIGIDBODIES_COLLISION
#define DEMO_RIGIDBODIES_COLLISION

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
	bool demoRotation;


public:

	GLFWwindow* window;
	Camera camera;

	DemoRigidBodiesCollision(GLFWwindow* newWindow, Camera newCamera, bool _demoRotation = false)
	{
		window = newWindow;
		camera = newCamera;
		demoRotation = _demoRotation;
		Init();
	}

	void Init()
	{
		std::cout << "Creation des RigidBodies cubes et plan" << std::endl;

		std::vector<Vector3D> listePositions{Vector3D(2.5,5,2),Vector3D(-10,5,-2) };//inserer des positions pour les tests
		std::vector<Vector3D> listeVelocites{Vector3D(-10,-10,0),Vector3D(10,-10,0) };//inserer des velocites pour les tests

		//Creation cubes (2)
		for (int i = 0; i < 2; i++)
		{
			RigidBody* rb = CreerCube(listePositions[i], listeVelocites[i], i);
			listeRigidBody.push_back(rb);
			ShapeRenderer* shapeRenderer = new ShapeRenderer(rb);
			listeShapeRenderer.push_back(shapeRenderer);
		}

		//Creation plan (1)
		RigidBody* rb = CreerPlan(Vector3D(-5,-5,0), Vector3D(10,10,10), 0);
		listeRigidBody.push_back(rb);
		ShapeRenderer* shapeRenderer = new ShapeRenderer(rb, rb->transform->getScale());
		listeShapeRenderer.push_back(shapeRenderer);


		std::cout << "Creation de la camera" << std::endl;

		//Mettre camera a un emplacement plus generique (vu de coté du plan)
		camera.Position = glm::vec3(-5, 5, 30);
	}

	//Rafraichissement des valeurs de position et de vitesse a valeur de temps variable, nous actualisons a la duree prise par la derniere frame pour s'executer.
	void UpdateFixedFrameRate(bool pause, float duration)
	{
		if (duration < 500)
		{
			//La duree de la frame precedente va nous permettre de simuler la physique de n-1, nous ne savons pas le temps que cette frame va prendre pour effectuer sa boucle de jeu.
			//Nous prenons donc volontairement une unite de retard pour la simulation.
			float newDuration = duration * 0.00005;

			float distanceFarthest = 0;

			//---------------MISE A JOUR DE LA PHYSIQUE DE NOS RIGIDBODIES---------------------------------

			for (size_t i = 0; i < listeRigidBody.size(); i++)
			{
				float dist = listeRigidBody[i]->transform->getPosition().getMax();
				if (dist > distanceFarthest) distanceFarthest = dist;
				RigidBody* rigidbody = listeRigidBody[i];
				if (rigidbody != nullptr)
				{
					if (rigidbody->primitive->getShape() != "Plan")
					{
						if (demoRotation == true)
						{
							Vector3D force = Vector3D(0, 2, 0);
							Vector3D localPoint = Vector3D(0.1, 0.25, 0.15);
							rigidbody->AddForceAtBodyPoint(force, localPoint);
							Vector3D gravity = Vector3D(0, -100, 0);
							rigidbody->SetVelocity(rigidbody->GetVelocity() + gravity * newDuration * rigidbody->GetMass());
							rigidbody->Integrate(newDuration);
						}
						else
						{
							Vector3D gravity = Vector3D(0, -100, 0);
							rigidbody->SetVelocity(rigidbody->GetVelocity() + gravity * newDuration * rigidbody->GetMass());
							rigidbody->Integrate(newDuration);
						}

					}
				}
			}

			//---------------DETECTION DES COLLISIONS ET RESOLUTION AVEC OCTREE---------------------------------

			//l'octree possede 8 regions distinctes qui divisent une partie d'espace cubique en 8 sous regions cubiques

			std::vector<OctreeDetection*> octreeObjects;
			for (size_t i = 0; i < listeRigidBody.size(); i++)
			{
				//si notre rigidbody ne possede pas de primitive nous n'avons pas de moyen de savoir quel detection appliquer
				if (!listeRigidBody[i]->primitive)
				{
					continue;
				}
				OctreeDetection* octreeObject = new OctreeDetection(listeRigidBody[i]);
				octreeObjects.push_back(octreeObject);
			}
			if (octreeObjects.size() == 0)//si nous n'avons aucun objet adequate dans l'espace ca ne sert a rien de detecter des collisions
			{
				return;
			}
			OctreeNode* entryNode = new OctreeNode();
			entryNode = entryNode->BuildOctree(Vector3D(0, 0, 0), 15, 2);
			for (int i = 0; i < octreeObjects.size(); i++) //on insert chacun des objets dans une des cases de l'octree
			{
				entryNode->InsertObject(octreeObjects[i]);
			}

			CollisionData* data = new CollisionData();
			data->contactLeft = 50;
			entryNode->TestAllCollisions(data);//on teste les collisions entre les objets des memes regions

			//Pour les contacts detectes, nous les resolvons.
			if (data->contactLeft < 50)//contact left correspond au nombre de contact generes au total dans ce tour de boucle
			{
				for (int i = 0; i < 50 - data->contactLeft; i++) 
				{
					data->contact[i]->resolve(newDuration);//on resoud les collisions si nous en avons detectes dans les sous regions
				}
			}
		}
	}

	//gere l'affichage et est appelee a chaque tour de boucle.
	void DisplayOpenGL()
	{
		for (int i = 0; i < listeShapeRenderer.size(); i++)
		{
			listeShapeRenderer[i]->render(window, camera);
		}
	}

	//permet la creation d'un cube avec les parametres souhaites
	RigidBody* CreerCube(Vector3D cubePosition, Vector3D cubeVelocity, int index)
	{
		int _index = index++;
		Transform* transform = new Transform("RigidBodyCube : " + std::to_string(_index));
		transform->setPosition(cubePosition);

		Boite* boite = new Boite();
		Plan* plan = new Plan();

		RigidBody* rb = new RigidBody(transform, cubeVelocity, boite, boite, plan);//Donnera une boite
		rb->Initialize(1, 0.9, 0.9, CubeBis(1, Vector3D(1, 1, 1)));
		return rb;
	}

	//permet la creation d'un cube simulant un plan avec les parametres souhaites
	RigidBody* CreerPlan(Vector3D planPosition, Vector3D scale, int index)
	{
		int _index = index++;
		Transform* transform = new Transform("RigidBodyPlan : " + std::to_string(_index), scale);
		transform->setPosition(planPosition);

		Boite* boite = new Boite();
		Plan* plan = new Plan();

		RigidBody* rb = new RigidBody(transform, Vector3D(0,0,0), plan, boite, plan);//Donnera un plan
		rb->Initialize(1, 0.9, 0.9, CubeBis(1, Vector3D(1, 1, 1)));
		return rb;
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
			,,,
		};
		return Matrix33(values);
	}
	*/
};

#endif DEMO_RIGIDBODIES_COLLISION
