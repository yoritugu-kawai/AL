#pragma once
#include<Matrix4x4.h>
#include<cassert>
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth);