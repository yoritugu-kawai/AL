#include "EnemyBullet.h"
#include"MyClass/chara/Player.h"
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocuty) {

	model_ = model;
	//長さ
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
	//
	
	textureHandle_ = TextureManager::Load("bullet2.png");
	worldTransform_.Initialize();
	
	worldTransform_.translation_ = position;

	velocuty_ = velocuty;
}

void EnemyBullet::Update() {
	//
	Vector3 toPlayer = {};

	toPlayer.x = player_->GetWorldTransform().matWorld_.m[3][0] - worldTransform_.translation_.x;
	toPlayer.y = player_->GetWorldTransform().matWorld_.m[3][1] - worldTransform_.translation_.y;
	toPlayer.z = player_->GetWorldTransform().matWorld_.m[3][2] - worldTransform_.translation_.z;

	Vector3 NomalisePlayer = Normalize(toPlayer);
	Vector3 NomalizeVelocity = Normalize(velocuty_);

	velocuty_ = SlerpFanc(NomalizeVelocity, NomalisePlayer, 0.05f);
	//
	Vector3 velocity = velocuty_;
	float velocityXZ = sqrt(velocity.x * velocity.x + velocity.z * velocity.z);

	float heightY = -velocity.y;

	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);

	worldTransform_.rotation_.x = std::atan2(heightY, velocityXZ);
	//

	worldTransform_.UpdateMatrix();

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
Vector3 EnemyBullet::SlerpFanc(Vector3 start, Vector3 end, float t) {

	float dot = start.x * end.x + start.y * end.y + start.z * end.z;
	float theta = std::acos(dot) * t;
	Vector3 relative = {end.x - start.x * dot, end.y - start.y * dot, end.z - start.z * dot};
	relative = Normalize(relative);
	Vector3 result = {
	    start.x * std::cosf(theta) + relative.x * std::sinf(theta),
	    start.y * std::cosf(theta) + relative.y * std::sinf(theta),
	    start.z * std::cosf(theta) + relative.z * std::sinf(theta)};

	return result;
}
