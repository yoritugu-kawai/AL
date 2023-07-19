#pragma once
#include "Input.h"
#include "MyClass/chara/PlayerBullet.h"
#include "TextureManager.h"
#include "MyClass/math/TransformNormal.h"
#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Player {
public:
	Player();
	~Player();
	void Initialize();

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();
	Vector3 GetWorldPosition();

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
	//
	

};
