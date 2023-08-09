#pragma once
#include "Input.h"
#include "MyClass/chara/EnemyBullet.h"
#include "MyClass/math/ALL.h"
#include "Subract.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Player;
class GameScene;
class Enemy {
public:
	enum class Phase {
		Approach, // 接近
		Leave,    // 離脱
	};

	Enemy();
	~Enemy();
	//初期化
	void Initialize(Vector3 pos);
	void ApproachInitialize();
	//更新
	void Update();
	void ApproachUpdate();
	void LeaveUpdate();
	//描画
	void Draw(ViewProjection viewProjection_);
	//弾
	void Fire();
	//セッター
	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gemeScene) { gameScene_ = gemeScene; }
	//ゲッター
	Vector3 GetWorldPosition();
	float GetRadius() { return radius_; }
	//当たり判定
	void OnCollision();
	// フラグ
	bool IsDead() const { return isDead_; }



private:
	uint32_t textureHandle_ = 0u;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	const float speed = -0.05f;
	Vector3 enemyVelocty_ = {0.0f, 0.0f, speed};
	//動き変換
	
	static void (Enemy::*spPhaseTable[])();
	Phase phase_ = Phase();
	//弾
	EnemyBullet* bullet_ = nullptr;
	//std::list<EnemyBullet*> bullets_;
	//
	static const int kFreInterval = 60;
	int32_t tim = 0;
	//当たり判定
	Input* input_ = nullptr;
	Player* player_ = nullptr;
	Vector3 distance;
	const float radius_ = 2.0f;
	// ゲームシーン
	GameScene* gameScene_ = nullptr;
	bool isDead_ = false;
};
