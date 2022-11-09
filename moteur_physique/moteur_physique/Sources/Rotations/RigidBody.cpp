#include "Rotations/RigidBody.h"

#define _USE_MATH_DEFINES
#include <math.h>

//Permet d'initialiser le rigidBody et lui assigner les valeurs correspondantes.
void RigidBody::Initialize(float mass, float damping, float angularDamping, Matrix33 tenseurInertie)
{
	inverseMasse = 1 / mass;
	damping = damping;
	m_angularDamping = angularDamping;
	SetInertieTenseur(tenseurInertie);
	CalculateDerivedData();
}

//Permet de déterminer la nouvelle position, velocity, rotation, orientation d'un rigidBody, appelé tous les pas de temps t dans la boucle de jeu.
void RigidBody::Integrate(float duration)
{
	//Acceleration
	Vector3D linearAcceleration = m_forceAccum * inverseMasse;
	Vector3D angularAcceleration = tenseurInertie * m_torqueAccum;

	//Vitesse
	velocity = velocity * pow(linearDamping, duration) + linearAcceleration * duration;
	rotation = rotation * pow(m_angularDamping, duration) + angularAcceleration * duration;

	//Position
	position = position + velocity * duration;
	orientation.UpdateByAngularVelocity(rotation, duration);

	transform->setPosition(position);
	transform->setRotation(orientation.ToEuler() * ((double)360 / (2 * M_PI)));

	//Update datas
	CalculateDerivedData();
	ClearAccumulator();
}

//-------------------------------------------------------------------------------METHODES UTILITAIRES-----------------------------------------------------------------------------------------------

//Permet de reset les accumulateurs 
void RigidBody::ClearAccumulator()
{
	m_forceAccum.clear();
	m_torqueAccum.clear();
}

void RigidBody::ComputeTenseurInertieWorld(Matrix33& inertieTenseur)
{
	Matrix33 transformMatrix33 = transformMatrix.ToMatrix33();
	inertieTenseur = transformMatrix33 * tenseurInertie;
	inertieTenseur *= transformMatrix33.Inverse();
}

//Permet d'obtenir la coordonnée du repère local dans le repère du monde
Vector3D RigidBody::LocalToWorld(Vector3D& local)
{
	return  transformMatrix.Inverse() * (local + position);
}

//Permet d'obtenir la coordonnée du monde dans le repère local
Vector3D RigidBody::WorldToLocal(Vector3D& world)
{
	return  transformMatrix.Inverse() * (world - position);
}

void RigidBody::CalculateDerivedData() 
{
	transformMatrix.SetOrientationAndPosition(orientation, position);
	ComputeTenseurInertieWorld(tenseurInertieWorld);
}

//Ajout d'une force dans l'accumulateur correspondant
void RigidBody::AddForce(const Vector3D& force) 
{
	m_forceAccum += force;
}

//Application d'une force a un point précis du rigidBody
void RigidBody::AddForceAtBodyPoint(const Vector3D& force, Vector3D& point)
{
	Vector3D world = LocalToWorld(point);
	AddForceAtPoint(force, world);
}

//==
void RigidBody::AddForceAtPoint(const Vector3D& force, Vector3D& point)
{
	AddForce(force);
	m_torqueAccum += Vector3D::vectorialProduct((position - point), force);
}

//----------------------------------------------------------------------------METHODES ADDITIONNELLES-----------------------------------------------------------------------------------

//Permet de calculer le resultat de la matrice apres application de la position et de la rotation
Matrix34 CalculatetransformMatrix(Matrix34& transformMatrix, Vector3D& position, Quaternion& orientation) {

	//on transforme chaque valeur de la matrice avec les valeurs du quaternion d'orientation
	transformMatrix.values[0] = 1 - (2 * orientation.value[2] * orientation.value[2]) - (2 * orientation.value[3] * orientation.value[3]);
	transformMatrix.values[1] = (2 * orientation.value[1] * orientation.value[2]) - (2 * orientation.value[0] * orientation.value[3]);
	transformMatrix.values[2] = (2 * orientation.value[1] * orientation.value[3]) + (2 * orientation.value[0] * orientation.value[2]);
	transformMatrix.values[3] = position.x;
	transformMatrix.values[4] = 2 * (orientation.value[1] * orientation.value[2]) + (2 * orientation.value[1] * orientation.value[3]);
	transformMatrix.values[5] = 1 - (2 * orientation.value[1] * orientation.value[1]) - (2 * orientation.value[3] * orientation.value[3]);
	transformMatrix.values[6] = (2 * orientation.value[2] * orientation.value[3]) - (2 * orientation.value[1] * orientation.value[1]);
	transformMatrix.values[7] = position.y;
	transformMatrix.values[8] = (2 * orientation.value[1] * orientation.value[3]) - (2 * orientation.value[1] * orientation.value[2]);
	transformMatrix.values[9] = (2 * orientation.value[2] * orientation.value[3]) + (2 * orientation.value[1] * orientation.value[1]);
	transformMatrix.values[10] = 1 - (2 * orientation.value[1] * orientation.value[1]) - (2 * orientation.value[2] * orientation.value[2]);
	transformMatrix.values[11] = position.z;
	return transformMatrix;
}