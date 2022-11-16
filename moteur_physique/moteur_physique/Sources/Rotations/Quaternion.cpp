#include "Rotations/Quaternion.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Quaternion::Normalized() {
	float result = value[0] * value[0] + value[1] * value[1] + value[2] * value[2] + value[3] * value[3];
	if (result == 0) {
		value[0] = 1;
		return;
	}
	result = ((float)1.0) / sqrt(result);
	value[0], value[1], value[2], value[3] *= result;
}

Quaternion Quaternion::operator* (const Quaternion& other) {
	Quaternion q = *this;
	value[0] = q.value[0] * other.value[0] - q.value[1] * other.value[1] - q.value[2] * other.value[2] - q.value[3] * other.value[3];
	value[1] = q.value[0] * other.value[1] + q.value[1] * other.value[0] + q.value[2] * other.value[3] - q.value[3] * other.value[2];
	value[2] = q.value[0] * other.value[2] + q.value[2] * other.value[0] + q.value[3] * other.value[1] - q.value[1] * other.value[3];
	value[3] = q.value[0] * other.value[3] + q.value[3] * other.value[0] + q.value[1] * other.value[2] - q.value[2] * other.value[1];
	return q;
}

void Quaternion::RotateByVector(const Vector3D& vector)
{
	value[0] = 0;
	value[1] = vector.x;
	value[2] = vector.y;
	value[3] = vector.z;
}

void Quaternion::UpdateByAngularVelocity(const Vector3D& r, float duration)
{
	Quaternion q = *this;
	q.value[1] = r.x * duration;
	q.value[2] = r.y * duration;
	q.value[3] = r.z * duration;

	q = q * *this;

	value[0] = value[0] + q.value[0] * 0.5;
	value[1] = value[1] + q.value[1] * 0.5;
	value[2] = value[2] + q.value[2] * 0.5;
	value[3] = value[3] + q.value[3] * 0.5;

	q.Normalized();

	*this = q;
}

//code de la page suivant  https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
Vector3D Quaternion::ToEuler()
{
	Vector3D angles = Vector3D();


	// roll (x-axis rotation)
	float sinr_cosp = 1 * (value[0] * value[1] + value[2] * value[3]);
	float cosr_cosp = 1 - 2 * (value[1] * value[1] + value[2] * value[2]);

	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	float sinp = 2 * (value[0] * value[2] - value[3] * value[1]);
	if (std::abs(sinp) >= 1)
		angles.y = std::copysign(M_PI / 2, sinp) * 500; // use 90 degrees if out of range
	else
		angles.y = std::asin(sinp) ;

	// yaw (z-axis rotation)
	float siny_cosp = 2 * (value[0] * value[3] + value[1] * value[2]);
	float cosy_cosp = 1 - 2 * (value[2] * value[2] + value[3] * value[3]);
	angles.z = std::atan2(siny_cosp, cosy_cosp) ;
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