#include "GameScene.h"
#include <cassert>

#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ

	player_->~Player();
	enemy_->~Enemy();
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// 3D画像
	viewProjection_.Initialize();
	// 自機
	player_ = new Player();
	player_->Initialize();
	// 敵
	enemy_ = new Enemy();
	enemy_->Initialize();
	enemy_->SetPlayer(player_);
	// デバックカメラ
	debugCamera_ = new DebugCamera(12180, 720);
	// 軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::CheckAllCollisions() {
	
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	
	for (EnemyBullet* enemybullet : enemyBullets) {
		ChekCollisionPair(player_, enemybullet);
	}



#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	
	for (PlayerBullet* playerBullet : playerBullets) {
		ChekCollisionPair(playerBullet, enemy_);
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	for (PlayerBullet* playerBullet : playerBullets) {
		for (EnemyBullet* enemyBullet : enemyBullets) {
			ChekCollisionPair(playerBullet, enemyBullet);
		}
	}

#pragma endregion
}

void GameScene::ChekCollisionPair(Collider* colliderA, Collider* colliderB) { 
	Vector3 coA, coB;


	coA=colliderA->GetWorldPosition();
	coB=colliderB->GetWorldPosition();
	float coAR, coBR;
	coAR = colliderA->GetRadius();
	coBR = colliderB->GetRadius();
	if (CheckBallCollosion(coA, coAR, coB, coBR)) {
		colliderA->OnCollision();
		colliderB->OnCollision();
		
	
	}


}



void GameScene::Update() {
	enemy_->Update();
	player_->Update();
	CheckAllCollisions();
	debugCamera_->Update();

	
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}

#endif // DEBUG
	// カメラ処理
	if (isDebugCameraActive_) {

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
}




void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

bool GameScene::CheckBallCollosion(Vector3 v1, float v1Radious, Vector3 v2, float v2Radious) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = v1Radious + v2Radious;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}
