#include "Rotations/Quaternion.h"

void Quaternion::Normalized() {
	float result = w * w + i * i + j * j + k * k;
	if (result == 0) {
		w = 1;
		return;
	}
	result = ((float)1.0) / sqrt(result);
	w, i, j, k *= result;
}

Quaternion Quaternion::operator* (const Quaternion& other) {
	Quaternion q = *this;
	w = q.w * other.w - q.i * other.i - q.j * other.j - q.k * other.k;
	i = q.w * other.i + q.i * other.w + q.j * other.k - q.k * other.j;
	j = q.w * other.j + q.j * other.w + q.k * other.i - q.i * other.k;
	k = q.w * other.k + q.k * other.w + q.i * other.j - q.j * other.i;
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
	Quaternion q;
	q.value[0] = 0;
	q.value[1] = vector.x;
	q.value[2] = vector.y;
	q.value[3] = vector.z;

	*this = q;
}

void UpdateByAngularVelocity(const Vector3D& rotation, float duration)
{

}