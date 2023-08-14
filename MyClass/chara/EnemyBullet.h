#pragma once
#include "Input.h"
#include "MyClass/math/Add.h"
#include <Model.h>
#include <WorldTransform.h>
#include"Collder.h"
class EnemyBullet : public Collider {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocuty);

	void Update();

	void Draw(const ViewProjection& viewProjection);
	static const int32_t kLifeTime = 60 * 5;
	bool IsDead() const { return isDead_; }
	void OnCollision() override;

	//
	float_t GetRadius() { return radius_; }

	Vector3 GetWorldPosition() override;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//
	Vector3 velocuty_;
	int32_t deathTimer_ = kLifeTime;
	//
	bool isDead_ = false;
	const float_t radius_ = 1.0f;
};