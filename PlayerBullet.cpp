#include "PlayerBullet.h"
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocuty) {
	model_ = model;

	textureHandle_ = TextureManager::Load("bullet.png");
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	// 速度
	velocuty_ = velocuty;
}

void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix();
	//速度
	worldTransform_.translation_ = Add(worldTransform_.translation_,velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}