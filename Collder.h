#pragma once
#include"Vector3.h"
class Collider {
public:
	// セッター
	void steRadius(float radius) { radius_ = radius; }
	// ゲッター
	float GetRadius() { return radius_; }
	virtual void OnCollision() = 0;
	virtual Vector3 GetWorldPosition() = 0;

private:
	float radius_ = 1.0f;
};
