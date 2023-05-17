#pragma once
#include "Input.h"
#include <Model.h>
#include <PlayerBullet.h>
#include <WorldTransform.h>
#include<list>
class Player {
public:
	~Player();
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();

private:
	/*画像*/
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	/*操作キー*/
	Input* input_ = nullptr;
	/*弾*/
	PlayerBullet* bullet_ = nullptr;
	std::list<PlayerBullet*> bullets_;
};
