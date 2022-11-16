#include "Rotations/Quaternion.h"
#define _USE_MATH_DEFINES
#include <math.h>

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



Vector3D Quaternion::ToEuler()
{
	Vector3D angles = Vector3D();

	// roll (x-axis rotation)
	float sinr_cosp = 2 * (value[0] * value[1] + value[2] * value[3]);
	float cosr_cosp = 1 - 2 * (value[1] * value[1] + value[2] * value[2]);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	float sinp = 2 * (value[0] * value[2] - value[3] * value[1]);
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp);

	// yaw (z-axis rotation)
	float siny_cosp = 2 * (value[0] * value[3] + value[1] * value[2]);
	float cosy_cosp = 1 - 2 * (value[2] * value[2] + value[3] * value[3]);
	angles.z = std::atan2(siny_cosp, cosy_cosp);
	return angles;
}

void Quaternion::SetByEulerRotation(Vector3D euler) {
	double cy = cos(euler.z * 0.5);
	double sy = sin(euler.z * 0.5);
	double cp = cos(euler.y * 0.5);
	double sp = sin(euler.y * 0.5);
	double cr = cos(euler.x * 0.5);
	double sr = sin(euler.x * 0.5);

	value[0] = cr * cp * cy + sr * sp * sy;
	value[1] = sr * cp * cy - cr * sp * sy;
	value[2] = cr * sp * cy + sr * cp * sy;
	value[3] = cr * cp * sy - sr * sp * cy;


}