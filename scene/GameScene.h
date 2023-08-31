#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<sstream>
//
#include "DebugCamera.h"
#include "MyClass/camera/RailCamera.h"
#include "MyClass/chara/Enemy.h"
#include "MyClass/chara/Player.h"
#include "MyClass/chara/Sktdome.h"
#include "TextureManager.h"
/// <summary>
/// ゲームシーン
/// </summary>
enum GAME { START, PLAY, CLEAR, OVER };

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
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();
	/// <summary>
	/// ゲームシーンの弾
	/// </summary>
	void AddEnemyBullet(EnemyBullet*enemyBullet);
    /// <summary>
    /// 敵データ読み込み
    /// </summary>
	void LoadEnemyPopData();
    /// <summary>
    /// 敵コマンド更新
    /// </summary>
	void UpdateEnemyPopCommands();
    private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// 3D画像
	Model* model_ = nullptr;

	ViewProjection viewProjection_;
	// 自機
	Player* player_ = nullptr;
	// 敵
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemys_;
	// デバックカメラ
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	// カメラ
	RailCmamera* railCmamera_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary
	/// 
	EnemyBullet* enemyBullet_ = nullptr;
	std::list<EnemyBullet*> enemyBullets_;
	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	//待機タイム
	bool isTim = true;
	int waitingTim = 120;
	//
	GAME Game;
	XINPUT_STATE joystate;
	int32_t gameCount;
	int32_t countDwun;
	Sprite* start_ = nullptr;
	Sprite* clear_ = nullptr;
	Sprite* over = nullptr;
};
