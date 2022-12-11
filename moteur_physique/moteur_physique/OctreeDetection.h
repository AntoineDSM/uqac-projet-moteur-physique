#pragma once
#include "Vector3D/Vector3D.h"
#include "Transform.h"
#include "Rotations/RigidBody.h"
#include "ContactResolution.h"

using namespace moteurJeux;

//Impl�mentation de la classe octree, octree est une structure de donn�e permettant de trier des donn�es dans un espace tridimensionnel. Ici nos donn�es sont des transforms
//cube/plan/...), l'objectif dans un tri est de ne tester ensuite que les transforms situ�s dans la m�me r�gion de l'espace.
struct OctreeDetection {

public:
	OctreeDetection(RigidBody* m_rb);

	Vector3D m_center;
	float m_radius;
	RigidBody* m_rb;
	OctreeDetection* m_nextObject;
};

//le noeud d'un octree correspond a une region de l'espace, centre, taille, transforms presents... lors de la construction nous associerons l'ensemble de ces elements.
struct OctreeNode {

public : 
	Vector3D m_center;
	float m_halfWidth;
	OctreeNode* m_childrens[8];
	OctreeDetection* m_objectList;

	int	getChildIndex(const Vector3D& objectPos);
	void InsertObject(OctreeDetection* obj);
	void TestAllCollisions(CollisionData *data);
	void TestCollision(OctreeDetection* a, OctreeDetection* b, CollisionData* collisionData);
	OctreeNode* BuildOctree(Vector3D center, float halfWidth, int maxDepth);
};
