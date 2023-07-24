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
	delete modelSkydome_;
	delete skydome_;
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
	//
	modelSkydome_ = Model::CreateFromOBJ("CelestialSphere", true);
	skydome_=new Skydome();
	skydome_->Initialize(modelSkydome_);


	// デバックカメラ
	debugCamera_ = new DebugCamera(12180, 720);
	// 軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB; // 弾
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();
	for (EnemyBullet* enemybullet : enemyBullets) {
		posB = enemybullet->GetWorldPosition();

		float distanceAB = Length(Subtract(posA, posB));
		float RadiusAB = (player_->GetRadius() + enemybullet->GetRadius());
		if (distanceAB <= RadiusAB) {

			player_->OnCollision();
			enemybullet->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* playerBullet : playerBullets) {
		posB = playerBullet->GetWorldPosition();
		float distanceAB = Length(Subtract(posA, posB));

		if (distanceAB<=enemy_->GetRadius()+playerBullet->GetRadius()) {

			enemy_->OnCollision();
			playerBullet->OnCollision();
		}
	}

#pragma endregion


#pragma region 自弾と敵弾の当たり判定

	for (PlayerBullet* playerBullet : playerBullets) {
		for (EnemyBullet* enemyBullet : enemyBullets) {
			posA = enemyBullet->GetWorldPosition();
			posB = playerBullet->GetWorldPosition();

			float distanceAB = Length(Subtract(posA, posB));
			
			if (distanceAB <= enemyBullet->GetRadius() + playerBullet->GetRadius()) {

				enemyBullet->OnCollision();
				playerBullet->OnCollision();
			}
		}
	}

#pragma endregion
}



void GameScene::Update() {
	enemy_->Update();
	player_->Update();
	CheckAllCollisions();
	debugCamera_->Update();
	skydome_->Update();

	
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
	skydome_->Draw(viewProjection_);

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

