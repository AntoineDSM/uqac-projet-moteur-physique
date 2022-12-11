#include "ContactRigidBody.h"

ContactRigidBody::ContactRigidBody(RigidBody* r1, RigidBody* r2, float restitution, float penetration) :
	m_restitution(restitution), m_penetration(penetration)
{
	m_rigidbodies[0] = r1;
	m_rigidbodies[1] = r2;
	if (r2 != nullptr) {
		m_contactNormal = Vector3D::get_normalization_2(m_rigidbodies[0]->transform->getPosition() - m_rigidbodies[1]->transform->getPosition());
	}
	else {
		m_contactNormal = Vector3D(0, 1, 0);
	}
}

void ContactRigidBody::resolve(float duration)
{
	//resolveVelocity();
	//resolveInterpretation();
}

float ContactRigidBody::calculateSeperatingVelocity() const
{
	if (m_rigidbodies[1] != nullptr)
		return (float)Vector3D::scalarProduct_2((m_rigidbodies[0]->GetVelocity() - m_rigidbodies[1]->GetVelocity()), m_contactNormal);
	else
		return (float)Vector3D::scalarProduct_2(m_rigidbodies[0]->GetVelocity(), m_contactNormal);
}

void ContactRigidBody::printInfoContact() const
{
	std::cout << "\t---Contact detecté---" << std::endl
		<< "------------------" << std::endl
		<< "Nom de l'objet 1: " << m_rigidbodies[0]->transform->getName() << std::endl
		<< "Nom de l'objet 2: " << m_rigidbodies[1]->transform->getName() << std::endl
		<< "Point de contact: " << m_contactPoint.x << " " << m_contactNormal.y << " " << m_contactNormal.z << std::endl
		<< "Normale du contact: " << m_contactNormal.x << " " << m_contactNormal.y << " " << m_contactNormal.z << std::endl
		<< "Vitesse de séparation: " << calculateSeperatingVelocity() << std::endl
		<< "Penetration: " << m_penetration << std::endl
		<< "Restitution: " << m_restitution << std::endl << std::endl;
}
