#pragma once
#include "Primitive.h"


class Boite : public Primitive
{
public:
	Vector3D m_halfSize;

	Vector3D vertices[8] =
	{
		Vector3D{-m_halfSize.x, -m_halfSize.y, -m_halfSize.z},
		Vector3D{-m_halfSize.x, -m_halfSize.y, +m_halfSize.z},
		Vector3D{-m_halfSize.x, +m_halfSize.y, -m_halfSize.z},
		Vector3D{-m_halfSize.x, +m_halfSize.y, +m_halfSize.z},
		Vector3D{+m_halfSize.x, -m_halfSize.y, -m_halfSize.z},
		Vector3D{+m_halfSize.x, -m_halfSize.y, +m_halfSize.z},
		Vector3D{+m_halfSize.x, +m_halfSize.y, -m_halfSize.z},
		Vector3D{+m_halfSize.x, +m_halfSize.y, +m_halfSize.z}
	};

	Boite()
	{
		//nothing to be add here
	}


	void Initialize(Vector3D halfSize = Vector3D(0.5f, 0.5f, 0.5f), Matrix34* offset = new Matrix34());
	Vector3D getHalfSize();
	const Vector3D& getVertex(int i) const;
	void setHalfSize(Vector3D halfSize);
};