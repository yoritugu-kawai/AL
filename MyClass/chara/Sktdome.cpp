#include "Sktdome.h"

void Skydome::Initialize(Model* model) {
	assert(model);

	this->model_ = model;

	worldTransform_.scale_.x = 100.0f;
	worldTransform_.scale_.y = 100.0f;
	worldTransform_.scale_.z = 100.0f;
	worldTransform_.Initialize();
}

void Skydome::Update() {

worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

worldTransform_.TransferMatrix();
}

void Skydome::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);


}
