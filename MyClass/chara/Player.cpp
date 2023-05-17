#include "MyClass/chara/Player.h"
#include "MyClass/math/TransformNormal.h"
#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include <ImGuiManager.h>
#include <cassert>

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}
void Player::Initialize(Model* model, uint32_t textureHandle) {
	/*画像*/
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}
void Player::Attack() {

	if (input_->PushKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		velocity = TransFormNormal(velocity, worldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);
		bullets_.push_back(newBullet);
	}
}

void Player::Update() {
	/*画像*/
	worldTransform_.TransferMatrix();
	/*操作キー*/
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	float inputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	ImGui::Begin(" ");
	ImGui::SliderFloat3("Player", inputFloat3, -33.0f, 33.0f);
	ImGui::End();
	// 移動制限
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 18;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	/*弾*/
	Attack();

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	// 回転
	const float kRotSpeed = 0.2f;
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {

		worldTransform_.rotation_.y += kRotSpeed;
	}
	// 速度
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
}

void Player::Draw(ViewProjection viewProjection_) {
	/*画像*/
	model_->Draw(this->worldTransform_, viewProjection_, this->textureHandle_);
	/*操作キー*/
	input_ = Input::GetInstance();
	/*弾*/
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
}
