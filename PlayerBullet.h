#pragma once
#include "Input.h"
#include <Model.h>
#include <WorldTransform.h>
class PlayerBullet {
public:
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	/*画像*/
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
