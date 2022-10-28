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
	float valPos = values[0] * values[4] * values[8] + values[3] * values[7] * values[2] + values[6] * values[1] * values[5];
	float valNeg = values[0] * values[7] * values[5] - values[6] * values[7] * values[2] - values[3] * values[1] * values[8];
	float detVal = valPos - valNeg;

	if (detVal == 0) return;

}


void Matrix34::SetOrientationAndPosition(const Quaternion& q, const Vector3D& p) {

}


Vector3D Matrix34::TransformPosition(const Vector3D& vector) {

}

Vector3D Matrix34::TransformDirection(const Vector3D& vector) {

}
