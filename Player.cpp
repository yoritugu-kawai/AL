#include"Player.h"
#include <cassert>
void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;

		worldTransform_.Initialize();




}

void Player::Update() { 
	worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection viewProjection_) {

model_->Draw(this->worldTransform_, viewProjection_, this->textureHandle_);

}
