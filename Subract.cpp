#include"Subract.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <cmath>
//減算 
Vector3 Subract(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
//毎積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result{};
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}
float Length(const Vector3& v) {
	float result{};
	result = sqrt(Dot(v, v));
	return result;
}
//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result{};
	float length = Length(v);
	if (length != 0.0f) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}