#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocuty) {

	model_ = model;

	textureHandle_ = TextureManager::Load("bullet2.png");
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocuty_ = velocuty;
}

void EnemyBullet::Update() {

	worldTransform_.UpdateMatrix();

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
