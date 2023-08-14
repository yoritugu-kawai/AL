#pragma once
#include "Input.h"
#include "MyClass/math/Add.h"
#include <Model.h>
#include <WorldTransform.h>
#include<numbers>
#include"Subract.h"
class Player;

class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocuty);

	void Update();

	void Draw(const ViewProjection& viewProjection);
	
	void SetPlayer(Player* player) { player_ = player; }

	static const int32_t kLifeTime = 60 * 5;
	bool IsDead() const { return isDead_; }

private:
	Vector3 SlerpFanc(Vector3 start, Vector3 end, float t);
	//
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	//
	Player* player_ = nullptr;
	//
	Vector3 velocuty_;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};