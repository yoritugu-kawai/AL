#pragma once
#include "Input.h"
#include "MyClass/chara/PlayerBullet.h"
#include "MyClass/math/Add.h"
#include "MyClass/math/Affine.h"
#include "MyClass/math/TransformNormal.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
#include"Collder.h"
#include<CollisionConfig.h>
class Player : public Collider {
public:
	Player();
	~Player();
	void Initialize();

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();
	void OnCollision() override;
	Vector3 GetWorldPosition() override;
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	float GetRadius() { return radius_; }

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
	const float radius_ = 2.0f;
};
