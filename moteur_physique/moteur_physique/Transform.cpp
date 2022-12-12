#include "Transform.h"

//-------------------------------------------------------METHODES DE LA CLASSE TRANSFORM---------------------------------------------------------------------

//Constructeur
Transform::Transform(std::string _name)
{
	name = _name;
}

//------------------------------------------------------------------GETTER & SETTER--------------------------------------------------------------------

void Transform::setPosition(Vector3D _position)
{
	position.x = _position.x;
	position.y = _position.y;
	position.z = _position.z;
}

void Transform::setRotation(Vector3D _rotation)
{
	rotation.x = _rotation.x;
	rotation.y = _rotation.y;
	rotation.z = _rotation.z;
}

Vector3D Transform::getPosition() {
	return position;
}

Vector3D Transform::getRotation() {
	return rotation;
}

Vector3D Transform::getScale() 
{
	return scale;
}

std::string Transform::getName()
{
	return name;
}