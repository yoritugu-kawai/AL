#pragma once
#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Enemy {
public:
	Enemy();
	~Enemy();
	void Initialize();

	void Update();

	void Draw(ViewProjection viewProjection_);
	enum class Phase {
		Approach,
		Leave,
	};

private:
	uint32_t textureHandle_ = 0u;
	Model* model_ = nullptr;

	WorldTransform worldTransform_;
};
