#include "OctreeDetection.h"

OctreeDetection::OctreeDetection(RigidBody* rb)
{
	m_center = rb->transform->getPosition();
	if (rb->primitive->getShape() == "Boite") {
		m_radius = rb->primitiveBoite->getHalfSize().getMax() * 1.41421356f;		//Le chiffre 1.41421356 est une approximation de racine de 2
	}
	else {	//Si c'est un plan alors la rayon est nul
		m_radius = 0;
	}
	m_rb = rb;
}

OctreeNode* OctreeNode::BuildOctree(Vector3D center, float halfWidth, int maxDepth)
{
	if (maxDepth <= 0) return nullptr;
	else {
		OctreeNode* returnNode = new OctreeNode();
		returnNode->m_center = center;
		returnNode->m_halfWidth = halfWidth;
		returnNode->m_objectList = nullptr;

		Vector3D offset;
		float step = returnNode->m_halfWidth * .5f;

		for (int i = 0; i < 8; i++) {
			//les opérations sur les bits ci-dessous nous permettent d'inverser ou non les valeurs x, y, z du centre d'une region. 
			offset.x = ((i & 1) ? step : -step);
			offset.y = ((i & 2) ? step : -step);
			offset.z = ((i & 4) ? step : -step);
			returnNode->m_childrens[i] = BuildOctree(returnNode->m_center + offset, step, maxDepth - 1);
		}
		return returnNode;
	}
}

OctreeNode::OctreeNode()
{
}

int OctreeNode::getChildIndex(const Vector3D& objectPos)
{
	int index = 0;
	if (objectPos.x > m_center.x) index += 1;
	if (objectPos.y > m_center.y) index += 2;
	if (objectPos.z > m_center.z) index += 4;
	return index;
}

void OctreeNode::InsertObject(OctreeDetection* obj)
{
	int index = 0;
	int straddle = 0; //Chevauchement

	for (int i = 0; i < 3; i++) {
		float delta = (float)obj->m_center.getValues()[i] - (float)m_center.getValues()[i];
		if (abs(delta) < m_halfWidth + obj->m_radius) {		//Si l'objet est en majorité dans une autre celulle, alors on ne l'ajoute pas
			straddle = 1;
			break;
		}
		//Il y a ici deux opération binaires: un "OU" et un décalage de bit vers la gauche. Ici, le décalage reviens à
		//mettre 2 à la puissance i.
		//La ligne suivante selectionne la cellule la plus appropriée, en regardant l'éloignement de l'objet par rapport au centre de la cellule.
		if (delta > 0.0f) index |= (1 << i);
	}
	if (!straddle && m_childrens[index]) {
		//Entièrement contenu dans un noeud enfant existant; on l'ajoute dans ce sous-arbre
		m_childrens[index]->InsertObject(obj);
	}
	else {
		//Il y a du chevauchement, ou aucun noeud enfant dans lequel aller, alors on connecte l'objet dans la liste connectée
		//de ce noeud
		obj->m_nextObject = m_objectList;
		m_objectList = obj;
	}
}

void OctreeNode::TestAllCollisions(CollisionData* collisionData)
{
	const int MAX_DEPTH = 3;
	static OctreeNode* ancestorStack[MAX_DEPTH];
	static int depth = 0;
	if (depth >= MAX_DEPTH) return;
	ancestorStack[depth++] = this;
	for (int n = 0; n < depth; n++) {
		OctreeDetection* a = ancestorStack[n]->m_objectList;
		bool aHasNextObject = true;
		bool bHasNextObject = true;
		while (aHasNextObject && a) {

			OctreeDetection* b = m_objectList;
			bHasNextObject = true;
			while (bHasNextObject && b) {
				if (a == b)
					break;
				TestCollision(a, b, collisionData);
				if (b->m_nextObject != nullptr) b = b->m_nextObject;
				else bHasNextObject = false;
			}
			if (a->m_nextObject != nullptr) a = a->m_nextObject;
			else aHasNextObject = false;
		}
	}
	for (int i = 0; i < 8; i++) {
		if (m_childrens[i]) m_childrens[i]->TestAllCollisions(collisionData);
	}
	depth--;
}

void OctreeNode::TestCollision(OctreeDetection* a, OctreeDetection* b, CollisionData* collisionData)
{
	ContactResolutions contactResolution = ContactResolutions();
	std::string shapeA = a->m_rb->primitive->getShape();
	std::string shapeB = b->m_rb->primitive->getShape();
	if (shapeA == "Plan") {
		if (shapeB == "Boite") {
			ContactResolutions::CollisionBoitePlan(*b->m_rb->primitiveBoite, *a->m_rb->primitivePlan, collisionData);
			return;
		}
	}
	if (shapeA == "Boite") {
		if (shapeB == "Plan") {
			ContactResolutions::CollisionBoitePlan(*a->m_rb->primitiveBoite, *b->m_rb->primitivePlan, collisionData);
			return;
		}
		else if (shapeB == "Boite") {
			ContactResolutions::CollisionBoiteBoite(*a->m_rb->primitiveBoite, *b->m_rb->primitiveBoite, collisionData);
			return;
		}
	}
}
