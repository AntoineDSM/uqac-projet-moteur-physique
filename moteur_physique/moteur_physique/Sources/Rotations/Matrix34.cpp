#include "Rotations/Matrix34.h"
#include <Rotations/Matrix33.h>

Matrix34& const Matrix34::operator*=(const Matrix34& other)
{
	Matrix34 mat = Matrix34();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			mat.values[i + j * 3] = 0;
			for (int k = 0; k < 3; k++)
				mat.values[i + j * 4] += values[k + i * 4] * other.values[j + k * 4];
		}
	for (int i = 0; i < 3; i++) {
		mat.values[3 + i * 4] = other.values[3 + i * 4];
	}
	return mat;
}

Matrix34 operator*(const Matrix34& premiereMatrice, const Matrix34& secondeMatrice)
{
	Matrix34 troisiemeMatrice = premiereMatrice;
	troisiemeMatrice *= secondeMatrice;
	return troisiemeMatrice;
}

Vector3D const Matrix34::operator* (const Vector3D& vector) {
	return Vector3D{
		vector.x * values[0] + vector.y * values[11] + vector.z * values[2] + values[3],
		vector.x * values[4] + vector.y * values[5] + vector.z * values[6] + values[7],
		vector.x * values[8] + vector.y * values[9] + vector.z * values[10] + values[11]
	};
}


Matrix34 Matrix34::Inverse()
{
	float valuesMatrix33[9] = { values[0] , values[1], values[2], values[4], values[5], values[6], values[8], values[9], values[10] };
	Matrix33 mat33 = Matrix33(valuesMatrix33);
	mat33 = mat33.Inverse();
	float valuesVectorRajout[3] = { values[3], values[7], values[11] };
	Vector3D vectDerniereColonne = mat33 * Vector3D(-1.0 * valuesVectorRajout[0], -1.0 * valuesVectorRajout[1], -1.0 * valuesVectorRajout[2]);
	return Matrix34(mat33, vectDerniereColonne);
}



void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p) {
	values[0] = 1 - (2 * q.value[2] * q.value[2] + 2 * q.value[3] * q.value[3]);
	values[1] = 2 * q.value[1] * q.value[2] + 2 * q.value[3] * q.value[0];
	values[2] = 2 * q.value[1] * q.value[3] - 2 * q.value[2] * q.value[0];

	values[4] = 2 * q.value[1] * q.value[2] - 2 * q.value[3] * q.value[0];
	values[5] = 1 - (2 * q.value[1] * q.value[1] + 2 * q.value[3] * q.value[3]);
	values[6] = 2 * q.value[2] * q.value[3] + 2 * q.value[1] * q.value[0];

	values[8] = 2 * q.value[1] * q.value[3] + 2 * q.value[2] * q.value[0];
	values[9] = 2 * q.value[2] * q.value[3] - 2 * q.value[1] * q.value[0];
	values[10] = 1 - (2 * q.value[1] * q.value[1] + 2 * q.value[2] * q.value[2]);

	values[3] = p.x;
	values[7] = p.y;
	values[11] = p.z;
}


Vector3D Matrix34::TransformPosition(const Vector3D& v) {
	return Vector3D{
		v.x * values[0] + v.y * values[1] + v.z * values[2] + values[3],
		v.x * values[4] + v.y * values[5] + v.z * values[6] + values[7],
		v.x * values[8] + v.y * values[9] + v.z * values[10] + values[11],
	};

}

Vector3D Matrix34::TransformDirection(const Vector3D& v) {
	return Vector3D{
		v.x * values[0] + v.y * values[1] + v.z * values[2],
		v.x * values[4] + v.y * values[5] + v.z * values[6],
		v.x * values[8] + v.y * values[9] + v.z * values[10],
	};
}

Matrix33 Matrix34::ToMatrix33() const
{
	{
		float values33[9];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				values33[i + 3 * j] = values[i + 4 * j];
			}
		}
		return Matrix33(values33);
	}
}