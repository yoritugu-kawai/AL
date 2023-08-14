#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocuty) {

	model_ = model;
	//長さ
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	//
	
	textureHandle_ = TextureManager::Load("bullet2.png");
	worldTransform_.Initialize();
	
	//
	float velocityXZ = sqrt(velocuty.x * velocuty.x + velocuty.z * velocuty.z);

	float heightY = -velocuty.y;
	worldTransform_.rotation_.y = std::atan2(velocuty.x, velocuty.z);
	worldTransform_.rotation_.x = std::atan2(heightY, velocityXZ);


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
