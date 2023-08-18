#include "MyClass/chara/PlayerBullet.h"
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocuty) {
	model_ = model;

	textureHandle_ = TextureManager::Load("bullet.png");
	worldTransform_.Initialize();

	worldTransform_.translation_ = position;
	// 速度
	velocuty_ = velocuty;
	isDead_ = false;
	steCollisionAttribute(kCollisionAttributePlayer);
	steCollisionMask(kCollisionAttributeEnemyr);
}

void PlayerBullet::Update() {
	worldTransform_.UpdateMatrix();
	// 速度
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	if (isDead_ == false) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}

void PlayerBullet::OnCollision() {

 isDead_ = true; 
}

Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;

	// ワールド行列の「平行移動成分」を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
