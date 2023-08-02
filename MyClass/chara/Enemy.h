#pragma once
#include "Input.h"
#include "MyClass/chara/EnemyBullet.h"
#include"MyClass/math/ALL.h"
#include"Subract.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Player;
class GameScene;
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
	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();
	void OnCollision();
	const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }
	float GetRadius() { return radius_; }
	//ゲームシーン

private:
	uint32_t textureHandle_ = 0u;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	const float speed = -0.05f;
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
	Player* player_ = nullptr;
	Vector3 distance;
	const float radius_ = 2.0f;
	//ゲームシーン
	GameScene* gameScene_ = nullptr;
};
