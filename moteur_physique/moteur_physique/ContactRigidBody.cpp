#include "ContactRigidBody.h"

ContactRigidBody::ContactRigidBody(RigidBody* r1, RigidBody* r2, float restitution, float penetration) : m_restitution(restitution), m_penetration(penetration)
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

//Resoud le contact et applique les modifications adequates a nos rigidbodies
void ContactRigidBody::resolve(float duration)
{
	//-----------------VELOCITY-----------------------------

	Vector3D velocity1 = m_rigidbodies[0]->GetVelocity();
	Vector3D velocity2 = Vector3D(0,0,0);
	if(m_rigidbodies[1] != nullptr)
	{
		if (m_rigidbodies[1]->primitive->getShape() != "Plan")
		{
			velocity2 = m_rigidbodies[1]->GetVelocity();
			velocity2 = moteurJeux::Vector3D::get_abs(velocity2);
		}
	}
	Vector3D velocity = velocity1 - velocity2;
	if (m_rigidbodies[1] != nullptr)
	{
		if (m_rigidbodies[1]->primitivePlan->getShape() == "Plan")
		{
				Vector3D resultante = velocity * m_rigidbodies[1]->primitivePlan->getNormal() * (double)-2;
				Vector3D resultanteRestitutition = m_rigidbodies[1]->primitivePlan->getNormal().getInverse(m_restitution);
				velocity = (velocity + resultante) * resultanteRestitutition;
		}
	}
	m_rigidbodies[0]->SetVelocity(velocity);
	if (m_rigidbodies[1] != nullptr)
	{
		if (m_rigidbodies[1]->primitive->getShape() != "Plan")
		{
			m_rigidbodies[1]->SetVelocity(velocity);
		}
	}
	
	//-----------------INTERPENETRATION-----------------------------

	Vector3D position1 = m_rigidbodies[0]->GetPosition();
	Vector3D position2 = Vector3D(0, 0, 0);
	if (m_rigidbodies[1] != nullptr)
	{
		if (m_rigidbodies[1]->primitive->getShape() != "Plan")
		{
			position2 = m_rigidbodies[1]->GetPosition();
			m_rigidbodies[0]->SetPosition(position1 + m_contactNormal * m_penetration * 0.5);
			m_rigidbodies[1]->SetPosition(position2 - m_contactNormal * m_penetration * 0.5);
		}
	}
	else
	{
		m_rigidbodies[0]->SetPosition(position1 + m_contactNormal * m_penetration);// *(double)2);
	}

	return;
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
	std::cout << "\t Contact detecte entre :" << std::endl
		<< "RigidBody : " << m_rigidbodies[0]->transform->getName() << std::endl
		<< "et RigidBody : " << m_rigidbodies[1]->transform->getName() << std::endl
		<< "La vitesse les separant est : " << calculateSeperatingVelocity() << std::endl
		<< "Le point de contact est : " << m_contactPoint.x << " " << m_contactPoint.y << " " << m_contactPoint.z << std::endl
		<< "La normale au point de contact est : " << m_contactNormal.x << " " << m_contactNormal.y << " " << m_contactNormal.z << std::endl
		<< "Le contact a ete resolu apres une penetration de : " << m_penetration << std::endl
		<< "Le coefficient de restitution du contact est de  : " << m_restitution << std::endl << std::endl;
}
