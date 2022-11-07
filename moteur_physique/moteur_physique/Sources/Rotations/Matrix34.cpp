#include "Rotations/Matrix34.h"

Matrix34 const Matrix34::operator* (const Matrix34& other)
{
	Matrix34 result;

	result.values[0] = other.values[0] * values[0] + other.values[4] * values[1] + other.values[8] * values[2];
	result.values[1] = other.values[1] * values[0] + other.values[5] * values[1] + other.values[9] * values[2];
	result.values[2] = other.values[2] * values[0] + other.values[6] * values[1] + other.values[10] * values[2];
	result.values[3] = other.values[3] * values[0] + other.values[7] * values[1] + other.values[11] * values[2] + values[3];
	result.values[4] = other.values[0] * values[4] + other.values[4] * values[5] + other.values[8] * values[6];
	result.values[5] = other.values[1] * values[4] + other.values[5] * values[5] + other.values[9] * values[6];
	result.values[6] = other.values[2] * values[4] + other.values[6] * values[5] + other.values[10] * values[6];
	result.values[7] = other.values[3] * values[4] + other.values[7] * values[5] + other.values[11] * values[6] + values[7];
	result.values[8] = other.values[0] * values[8] + other.values[4] * values[9] + other.values[8] * values[10];
	result.values[9] = other.values[1] * values[8] + other.values[5] * values[9] + other.values[9] * values[10];
	result.values[10] = other.values[2] * values[8] + other.values[6] * values[9] + other.values[10] * values[10];
	result.values[11] = other.values[3] * values[8] + other.values[7] * values[9] + other.values[11] * values[10] + values[11];

	return result;
}

Vector3D const Matrix34::operator* (const Vector3D& vector) {
	return Vector3D{
		vector.x * values[0] + vector.y * values[11] + vector.z * values[2] + values[3],
		vector.x * values[4] + vector.y * values[5] + vector.z * values[6] + values[7],
		vector.x * values[8] + vector.y * values[9] + vector.z * values[10] + values[11]
	};
}


Matrix34 Matrix34::Inverse() {
	float valPos = values[0] * values[5] * values[10] + values[4] * values[9] * values[2] + values[8] * values[1] * values[6];
	float valNeg = values[0] * values[9] * values[6] - values[8] * values[9] * values[2] - values[4] * values[1] * values[10];
	float detVal = valPos - valNeg;

	if (detVal == 0) return;

	values[0] = (1 / detVal) * (values[5] * values[10]) - (values[8] * values[9]);
	values[1] = (1 / detVal) * (values[2] * values[9]) - (values[1] * values[10]);
	values[2] = (1 / detVal) * (values[1] * values[6]) - (values[2] * values[5]);
	values[4] = (1 / detVal) * (values[6] * values[10]) - (values[4] * values[10]);
	values[5] = (1 / detVal) * (values[0] * values[10]) - (values[2] * values[8]);
	values[6] = (1 / detVal) * (values[2] * values[4]) - (values[0] * values[6]);
	values[8] = (1 / detVal) * (values[4] * values[9]) - (values[5] * values[8]);
	values[9] = (1 / detVal) * (values[4] * values[9]) - (values[0] * values[9]);
	values[10] = (1 / detVal) * (values[0] * values[5]) - (values[1] * values[4]);

	values[3] = -values[3];
	values[7] = -values[7];
	values[11] = -values[11];
}



void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p) {
	values[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
	values[1] = 2 * q.i * q.j + 2 * q.k * q.w;
	values[2] = 2 * q.i * q.k - 2 * q.j * q.w;

	values[4] = 2 * q.i * q.j - 2 * q.k * q.w;
	values[5] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
	values[6] = 2 * q.j * q.k + 2 * q.i * q.w;


	values[8] = 2 * q.i * q.k + 2 * q.j * q.w;
	values[9] = 2 * q.j * q.k - 2 * q.i * q.w;
	values[10] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);

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