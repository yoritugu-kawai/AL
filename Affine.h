﻿#pragma once
#include<Matrix4x4.h>
#include<Vector3.h>

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeRotataXMatrix(float radian);
Matrix4x4 MakeRotataYMatrix(float radian);
Matrix4x4 MakeRotataZMatrix(float radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);



