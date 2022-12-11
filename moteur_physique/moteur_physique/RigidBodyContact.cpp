#include "RigidBodyContact.h"


RigidBodyContact::RigidBodyContact(RigidBody* r1, RigidBody* r2, float restitution, float penetration) :
	m_restitution(restitution), m_penetration(penetration)
{
	m_rigidbodies[0] = r1;
	m_rigidbodies[1] = r2;
	if (r2 != nullptr) {
		m_contactNormal = moteurJeux::Vector3D::get_normalization_2((m_rigidbodies[0]->GetPosition() - m_rigidbodies[1]->GetPosition()));
	}
	else {
		m_contactNormal = Vector3D(0, 1, 0);
	}
}

void RigidBodyContact::resolve(float duration)
{
	//resolveVelocity();
	//resolveInterpretation();
}

float RigidBodyContact::calculateSeperatingVelocity() const
{
	if (m_rigidbodies[1] != nullptr)
		return (m_rigidbodies[0]->GetVelocity() - m_rigidbodies[1]->GetVelocity()).scalarProduct(m_contactNormal);
	else
		return m_rigidbodies[0]->GetVelocity().scalarProduct(m_contactNormal);
}

void RigidBodyContact::printInfoContact() const
{
	std::cout << "\t---Contact detecté---" << std::endl
		<< "------------------" << std::endl
		<< "Nom de l'objet 1: " << m_rigidbodies[0]->transform->name << std::endl
		<< "Nom de l'objet 2: " << m_rigidbodies[1]->transform->name << std::endl
		<< "Point de contact: " << pointContact.x << " " << pointContact.y << " " << pointContact.z << std::endl
		<< "Normale du contact: " << m_contactNormal.x << " " << m_contactNormal.y << " " << m_contactNormal.z << std::endl
		<< "Vitesse de séparation: " << calculateSeperatingVelocity() << std::endl
		<< "Penetration: " << m_penetration << std::endl
		<< "Restitution: " << m_restitution << std::endl << std::endl;
}
