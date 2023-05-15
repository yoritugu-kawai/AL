#pragma once

#include<Model.h>
#include<WorldTransform.h>
#include"Input.h"

class Player {
public:

	void Initialize(Model*model,uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

private:
	/*画像*/
	WorldTransform worldTransform_;
	
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	/*操作キー*/
	Input* input_ = nullptr;
	float inputFloat3[3] = {0, 0, 0};

};
