#include "MyClass/chara/Enemy.h"
#include <ImGuiManager.h>
Enemy::Enemy() {}
Enemy::~Enemy() { delete model_; }
void Enemy::Initialize() {
	worldTransform_.Initialize();
	textureHandle_ = TextureManager::Load("enemy.png");
	model_ = Model::Create();
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
}

void Enemy::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}