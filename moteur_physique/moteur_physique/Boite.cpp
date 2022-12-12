#include "Boite.h"

void Boite::Initialize(Vector3D _halfSize, Matrix34 _offset)
{
	halfSize = _halfSize;
	m_offset = _offset;
}

const Vector3D& Boite::getVertex(int i) const
{
	return vertices[i];
}

Vector3D Boite::getHalfSize() const
{
	return halfSize;
}

void Boite::setHalfSize(Vector3D halfSize)
{
	halfSize = halfSize;
}


std::string Boite::getShape() const
{
	return "Boite";
}