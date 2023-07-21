#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocuty) {

	model_ = model;

	textureHandle_ = TextureManager::Load("bullet2.png");
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;

	velocuty_ = velocuty;
	isDead_ = false;
}
Vector3 EnemyBullet::GetWorldPosition() {
	Vector3 worldPos;

	// ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
void EnemyBullet::OnCollision() { isDead_ = true; }

void EnemyBullet::Update() {

	worldTransform_.UpdateMatrix();

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	if (isDead_ == false) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}

