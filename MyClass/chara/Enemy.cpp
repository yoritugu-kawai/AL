#include "MyClass/chara/Enemy.h"
#include <ImGuiManager.h>
#include <cassert>
Enemy::Enemy() {}
Enemy::~Enemy() {
	delete model_;
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	
}
void Enemy::ApproachInitialize() {
	tim = kFreInterval;
}
void Enemy::Initialize() {
	worldTransform_.Initialize();
	worldTransform_.translation_.x = 5.0f;
	worldTransform_.translation_.z = 500.0f;
	textureHandle_ = TextureManager::Load("enemy.png");
	model_ = Model::Create();
	ApproachInitialize();
}



void Enemy::ApproachUpdate() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, enemyVelocty_);
	if (worldTransform_.translation_.z < -20.0f) {

		phase_ = Phase::Leave;
	}
	tim++;
	if (tim >= 60)
	{
		Fire();
		tim = 0;
	}
}

void Enemy::LeaveUpdate() { 
	worldTransform_.translation_.x -= 0.1f;
	worldTransform_.translation_.y += 0.1f;

}

void Enemy::Fire() {
	

		// 弾の速度

	
		const float kBulletSpeed = -1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = TransFormNormal(velocity, worldTransform_.matWorld_);

		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	    bullets_.push_back(newBullet);
	  

}


void Enemy::Update() {
	worldTransform_.TransferMatrix();
	// 移動
	Vector3 move{0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	move.z -= kCharacterSpeed;

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	switch (phase_) {
	case Phase::Approach:
		ApproachUpdate();
		break;
	case Phase::Leave:
		LeaveUpdate();
		break;
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
}

void Enemy::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}

}

