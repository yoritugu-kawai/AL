#include "MyClass/chara/Enemy.h"
#include "Player.h"
#include "GameScene.h"
#include <ImGuiManager.h>
#include <cassert>
Enemy::Enemy() {}
Enemy::~Enemy() {
	delete model_;
	
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	
	return worldPos;
}

void Enemy::ApproachInitialize() { tim = kFreInterval; }
void Enemy::Initialize(Vector3 pos) {
	worldTransform_.Initialize();
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z;
	textureHandle_ = TextureManager::Load("enemy.png");
	model_ = Model::Create();
	ApproachInitialize();
	isDead_ = false;
}

void Enemy::ApproachUpdate() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocty_);
	if (worldTransform_.translation_.z < -20.0f) {

		phase_ = Phase::Leave;
	}
	tim++;
	if (tim >= 60) {
		Fire();
		tim = 0;
	}
}

void Enemy::LeaveUpdate() {
	worldTransform_.translation_.x -= 0.1f;
	worldTransform_.translation_.y += 0.1f;
	tim++;
	if (tim >= 60) {
		Fire();
		tim = 0;
	}
}

void Enemy::OnCollision() { isDead_ = true; }

void Enemy::Fire() {

	assert(player_);
	const float kBulletSpeed = 1.0f;
	// Vector3 velocity(0, 0, kBulletSpeed);

	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = GetWorldPosition();
	distance = Subract(playerPos, enemyPos);
	Vector3 norma = Normalize(distance);

	// 弾の速度
	Vector3 velocity = {
	    norma.x,
		norma.y, 
		norma.z * kBulletSpeed

	};

	velocity = TransFormNormal(velocity, worldTransform_.matWorld_);

	EnemyBullet* newBullet = new EnemyBullet();
	
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	gameScene_->AddEnemyBullet(newBullet);
	//bullets_.push_back(newBullet);
}

void Enemy::Update() {

	worldTransform_.TransferMatrix();
	// 移動
	Vector3 move{0, 0, 0};
	const float kCharacterSpeed = 0.02f;
	move.z -= kCharacterSpeed;

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//switch (phase_) {
	//case Phase::Approach:
	//	ApproachUpdate();
	//	break;
	//case Phase::Leave:
	//	LeaveUpdate();
	//	break;
	//}

	(this->*spPhaseTable[static_cast<size_t>(phase_)])();
	float inputFloat[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	ImGui::Begin(" ");
	ImGui::SliderFloat3("Enemy", inputFloat, -10.0f, 3.0f);
	//ImGui::InputInt("Time", time);
	ImGui::End();
}


void Enemy::Draw(ViewProjection viewProjection_) {
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	}
}
