#pragma once

#ifndef RIGIDBODY
#define RIGIDBODY

#include "Matrix33.h"
#include "../../Transform.h"
#include "../Boite.h"
#include "../Plan.h"

class RigidBody {
public:

	Transform* transform;
	Primitive* primitive = new Primitive();
	Boite* primitiveBoite = new Boite();
	Plan* primitivePlan = new Plan();
	// calculates transform matrix from orientation and rotation
	Matrix34 transformMatrix;

private:

	// same as for Particle
	float inverseMasse;
	float linearDamping;
	Vector3D position;
	Vector3D velocity;
	// Orientation of the rigid body
	Quaternion orientation;
	// Angular velocity of the rigid body
	Vector3D rotation;
	//Calculates tenseur of inertia
	Matrix33 tenseurInertieInverse;
	Matrix33 tenseurInertieWorldInverse;
	//same as linear damping but for rotation
	float m_angularDamping;
	// Accumulated force added by ForceGenerator
	Vector3D m_forceAccum;
	// Accumulated torque added by ForceGenerator
	Vector3D m_torqueAccum;

public:

	RigidBody(Transform* _transform, Vector3D _velocity, Primitive* _primitive, Boite* boite, Plan* plan)
	{
		transform = _transform;
		primitive = _primitive;
		if (primitive->getShape() == "Boite")
		{
			primitiveBoite = boite;
		}
		else if (primitive->getShape() == "Plan")
		{
			primitivePlan = plan;
		}

		inverseMasse = 1.0f;
		linearDamping = 1.0f;
		m_forceAccum = Vector3D(0, 0, 0);
		m_torqueAccum = Vector3D(0, 0, 0);
		Vector3D _position = transform->getPosition();
		Vector3D _rotation = transform->getRotation();
		position = Vector3D(_position.x, _position.y, _position.z);
		velocity = _velocity;
		orientation = Quaternion(1, 0, 0, 0);
		orientation.RotateByVector(_rotation);
	}

	//Allow us to initialize our RB with some inputed values
	void Initialize(float mass, float damping, float angularDamping, Matrix33 tenseurInertie);

	// Integrate the rigid body by modifying position, orientation and velocities.
	void Integrate(float duration);

	// Add force on the Center of mass (no torque generated)
	void AddForce(const Vector3D& force);

	// Add force at a point in world coordinate.
	// Generate force and torque
	void AddForceAtPoint(const Vector3D& force, Vector3D& worldPoint);

	// Add force at a point in local coordinate.
	// the point is converted in world coordinated by using the transform matrix.
	// Generate force and torque
	void AddForceAtBodyPoint(const Vector3D& force, Vector3D& LocalPoint);

	// called each frame to reset m_forceAccum and m_torqueAccum
	void ClearAccumulator();

	//----------------------------------------------------------------------------METHODES COMMUNES A PARTICULES & AUTRES----------------------------------------------------------------------------------------

	inline Vector3D GetPosition() const
	{
		return position;
	}

	inline Quaternion GetRotation() const
	{
		return orientation;
	}

	inline Vector3D GetVelocity()
	{
		return velocity;
	}

	inline void SetPosition(Vector3D newPos)
	{
		position = newPos;
	}

	inline float GetMass() const
	{
		if (inverseMasse != 0) return 1 / inverseMasse;
		std::cout << "La masse de l'objet est infinie, c'est impossible." << std::endl;
		return -1;
	}

	inline void SetInertieTenseur(const Matrix33& _tenseurInertie)
	{
		tenseurInertieInverse = _tenseurInertie.Inverse();
	}

	inline void SetOrientation(Vector3D _pos)
	{
		orientation.SetByEulerRotation(_pos);
	}

	//----------------------------------------------------------------------------------------METHODES PRIVEES-----------------------------------------------------------------------------------------------------

private:

	// call each frame to calculate the transformMatrix and normalize the orientation.
	void CalculateDerivedData();

	void ComputeTenseurInertieWorld(Matrix33& inertiaTenseur);

	//return a local based pos to a world based pos
	Vector3D LocalToWorld(Vector3D& local);
	//return a world based pos to a local based pos
	Vector3D WorldToLocal(Vector3D& world);
};

#endif RIGIDBODY