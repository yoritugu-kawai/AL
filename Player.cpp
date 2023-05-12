#include"Player.h"
#include <cassert>
void Player::Initialize(Model* model, uint32_t textureHandle) { 
		/*�摜*/
	assert(model);
	this->model_ = model;
	this->textureHandle_ = textureHandle;

	worldTransform_.Initialize();




}

void Player::Update() { 
		/*�摜*/
	worldTransform_.TransferMatrix();
	    /*����L�[*/
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y+= kCharacterSpeed;
	}

}

void Player::Draw(ViewProjection viewProjection_) {
	/*�摜*/
	model_->Draw(this->worldTransform_, viewProjection_, this->textureHandle_);
	/*����L�[*/
	input_ = Input::GetInstance();


}
