#pragma once
#include "Input.h"
#include "MyClass/chara/PlayerBullet.h"
#include "MyClass/math/ALL.h"
#include "TextureManager.h"
#include <Model.h>
#include <WorldTransform.h>
#include <list>
class Player {
public:
	Player();
	~Player();
	void Initialize(Model* model, Vector3 position);

	void Update();

	void Draw(ViewProjection viewProjection_);

	void Attack();
	void OnCollision();
	Vector3 GetWorldPosition();
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	float GetRadius() { return radius_; }
	void SetParent(const WorldTransform*parent);

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
