#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <cmath>
#include<cassert>
#include<Matrix4x4.h>
#include<Vector3.h>

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);