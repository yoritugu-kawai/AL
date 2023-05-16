#include "PlayerBullet.h"
void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	model_ = model;

	textureHandle_ = TextureManager::Load("bullet.png");
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() { worldTransform_.UpdateMatrix(); }

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}