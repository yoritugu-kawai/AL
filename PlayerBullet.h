#pragma once
#include "Input.h"
#include <Add.h>
#include <Model.h>
#include <WorldTransform.h>
class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocuty);

	void Update();

	void Draw(const ViewProjection& viewProjection);
	static const int32_t kLifeTime = 60 * 5;
	bool IsDead() const { return isDead_; }

private:
	/*画像*/
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocuty_;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};
