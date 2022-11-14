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
	return q;
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

void Quaternion::UpdateByAngularVelocity(const Vector3D& r, float d)
{
	Quaternion q;
	q.value[0] = 0;
	q.value[1] = r.x * d;
	q.value[2] = r.y * d;
	q.value[3] = r.z * d;

	q = q * *this;

	w = w + q.w * 0.5;
	i = i + q.i * 0.5;
	j = j + q.j * 0.5;
	k = k + q.k * 0.5;
}