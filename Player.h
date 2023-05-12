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
	/*‰æ‘œ*/
	WorldTransform worldTransform_;
	
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	/*‘€ìƒL[*/
	Input* input_ = nullptr;

};
