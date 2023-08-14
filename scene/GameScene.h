#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
//
#include "DebugCamera.h"
#include "MyClass/chara/Enemy.h"
#include "MyClass/chara/Player.h"
#include "TextureManager.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	///衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// 3D画像

	ViewProjection viewProjection_;
	// 自機
	Player* player_ = nullptr;
	// 敵
	Enemy* enemy_ = nullptr;
	// デバックカメラ
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;

	/// <summary>
	/// コライダー
	/// </summary>
	void ChekCollisionPair(Collider* colliderA, Collider* colliderB);
	bool CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious);
};
