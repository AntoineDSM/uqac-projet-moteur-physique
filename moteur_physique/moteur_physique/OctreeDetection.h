#pragma once
#include "CollisionData.h"
#include "ContactResolution.h"

#ifndef OCTREE_DETECTION
#define OCTREE_DETECTION

//Inspiration du pseudo code vu en cours d'algorithmie et de structures de donnees avancees.
//Permet d'organiser un ensemble de donnees tridimensionnelles en partitionnant recursivement l espace. Diminue la complexite de notre systeme de detection de collision.
struct OctreeDetection
{
	//Constructeur
	OctreeDetection(RigidBody* entity);
	//situation dans l'espace tridimensionnel
	Vector3D m_center;
	//taille de l objet
	float m_radius;
	//RigidBody associe a cette donnee tridimensionnelle
	RigidBody* m_rb;
	//Objet voisin dans la hierarchie
	OctreeDetection* m_nextObject = nullptr;
};

//Noeud de notre arbre Octree, correspond a une region precise de l'espace et contient des elements OctreeDetection (des RigidBodies avec donnees tridimensionnelles)
struct OctreeNode 
{
	//Centre de la region concernee
	Vector3D m_center;
	//taille de la region concernee
	float m_halfWidth;
	//elements sous cette region, plus bas dans la hierarchie/plus partitionnes
	OctreeNode* m_childrens[8];
	//Elements presents dans cette region
	OctreeDetection* m_objectList;

	//Constructeur
	OctreeNode();

	//-------------------------------------------------------GETTERS & SETTERS---------------------------------------------------------------------------

	int	getChildIndex(const Vector3D& objectPos);

	//------------------------------------------------------METHODES ADDITIONNELLES----------------------------------------------------------------------

	//Inserer un objet dans l'arbre, donc le positionner a la bonne place dans la hierarchie
	void InsertObject(OctreeDetection* obj);

	//Permet de detecter si deux elements sont dans la meme region
	void TestAllCollisions(CollisionData* collisionData);

	//Permet de detecter si deux elements de la meme region se touchent
	void TestCollision(OctreeDetection* a, OctreeDetection* b, CollisionData* collisionData);

	//Permet de construire l'arbre recursivement
	static OctreeNode* BuildOctree(Vector3D center, float halfWidth, int maxDepth);

	//---------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif OCTREE_DETECTION
