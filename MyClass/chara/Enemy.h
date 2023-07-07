#pragma once
#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Enemy {
public:
	Enemy();
	~Enemy();
	void Initialize();

	void Update();
	void ApproachUpdate();
	void LeaveUpdate();
	void Draw(ViewProjection viewProjection_);


private:
	uint32_t textureHandle_ = 0u;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	const float speed = -0.5f;
	Vector3 enemyVelocty_ = {0.0f, 0.0f, speed};
	enum class Phase {
		Approach, // 接近
		Leave,    // 離脱
	};
	Phase phase_ = Phase();
};
