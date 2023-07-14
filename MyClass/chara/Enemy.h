﻿#pragma once
#include "Input.h"
#include "MyClass/chara/EnemyBullet.h"
#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include "MyClass/math/TransformNormal.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Enemy {
public:
	Enemy();
	~Enemy();
	void Initialize();
	void ApproachInitialize();

	void Update();
	void ApproachUpdate();
	void LeaveUpdate();
	void Draw(ViewProjection viewProjection_);
	void Fire();
	

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
	EnemyBullet* bullet_ = nullptr;
	std::list<EnemyBullet*> bullets_;
	//
	static const int kFreInterval = 60;
	int32_t tim = 0;
	//
	Input* input_ = nullptr;
};
