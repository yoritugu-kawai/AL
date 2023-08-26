#include "GameScene.h"
#include <cassert>

#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include <fstream>
GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ

	player_->~Player();
	// enemy_->~Enemy();

	for (Enemy* enemy : enemys_) {
		delete enemy;
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	delete debugCamera_;
	delete modelSkydome_;
	delete skydome_;
	delete railCmamera_;
}

void GameScene::Initialize() {
	//
	TextureManager::Load("anchor.png");
	//
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// 3D画像
	model_ = Model::Create();

	// ビューの初期化
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
	// 自機
	player_ = new Player();
	Vector3 playerPosition(0.0f, -5.0f, 20.0f);
	player_->Initialize(model_, playerPosition);

	// 敵
	LoadEnemyPopData();
	// 天球
	modelSkydome_ = Model::CreateFromOBJ("CelestialSphere", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);

	// デバックカメラ
	debugCamera_ = new DebugCamera(1280, 720);
	// カメラ
	railCmamera_ = new RailCmamera();
	Vector3 radian = {0.0f, 0.0f, 0.0f};
	railCmamera_->Initialize(player_->GetWorldPosition(), radian);
	player_->SetParent(&railCmamera_->GetWorldTransform());

	// 軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	// シーン切り替え

	Game = START;
	gameCount = 0;
}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB; // 弾
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();
	for (EnemyBullet* enemybullet : enemyBullets_) {
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

	for (Enemy* enemy : enemys_) {
		for (PlayerBullet* playerBullet : playerBullets) {
			posA = enemy->GetWorldPosition();
			posB = playerBullet->GetWorldPosition();
			float distanceAB = Length(Subtract(posA, posB));

			if (distanceAB <= enemy->GetRadius() + playerBullet->GetRadius()) {

				enemy->OnCollision();
				playerBullet->OnCollision();
				gameCount += 1;
			}
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	for (PlayerBullet* playerBullet : playerBullets) {
		for (EnemyBullet* enemyBullet : enemyBullets_) {
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

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

void GameScene::LoadEnemyPopData() {

	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());
	enemyPopCommands << file.rdbuf();
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {
	if (isTim) {
		waitingTim--;
		if (waitingTim <= 0) {
			isTim = false;
		}
		return;
	}
	std::string line;
	// コマンドループ
	while (std::getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);
		std::string word;

		std::getline(line_stream, word, ',');
		//"//"から始まるコメント
		if (word.find("//") == 0) {
			continue;
		}
		// PoPコマンド
		if (word.find("POP") == 0) {
			// X座標
			std::getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			// Y座標
			std::getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			// Z座標
			std::getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());
			// 敵発生

			enemy_ = new Enemy();
			enemys_.push_back(enemy_);
			enemy_->Initialize(Vector3(x, y, z));
			enemy_->SetGameScene(this);
			enemy_->SetPlayer(player_);
		} else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');
			// 待ち
			int32_t waitTim = atoi(word.c_str());
			// 待機開始
			isTim = true;
			waitingTim = waitTim;
			break;
		}
	}
}

void GameScene::Update() {
	switch (Game) {
	case START:
		if (!Input::GetInstance()->GetJoystickState(0, joystate)) {
			return;
		}
		if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

			Game = PLAY;
		}
		gameCount = 0;
		break;
	case PLAY:
		player_->Update(viewProjection_);
		UpdateEnemyPopCommands();
		for (Enemy* enemy : enemys_) {
			enemy->Update();
		}
		enemys_.remove_if([](Enemy* enemy) {
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}

			return false;
		});
		CheckAllCollisions();
		debugCamera_->Update();
		skydome_->Update();

		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Update();
		}
		enemyBullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
		});

#ifdef _DEBUG
		if (input_->TriggerKey(DIK_K)) {
			isDebugCameraActive_ = true;
		}

#endif // DEBUG
       // カメラ処理
		if (isDebugCameraActive_) {

			viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		} else {
			railCmamera_->Update();
			viewProjection_.matView = railCmamera_->GetViewProjection().matView;
			viewProjection_.matProjection = railCmamera_->GetViewProjection().matProjection;
			viewProjection_.TransferMatrix();
		}
		if (gameCount == 5) {
			Game = CLEAR;
		}
		break;
	case OVER:
		if (!Input::GetInstance()->GetJoystickState(0, joystate)) {
			return;
		}
		if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			Game = START;
		}
		break;
	case CLEAR:
		if (!Input::GetInstance()->GetJoystickState(0, joystate)) {
			return;
		}
		if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
			Game = START;
		}
		break;
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
	///
	switch (Game) {
	case START:
		break;
	case PLAY:
		player_->Draw(viewProjection_);

		for (Enemy* enemy : enemys_) {
			enemy->Draw(viewProjection_);
		}

		skydome_->Draw(viewProjection_);

		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Draw(viewProjection_);
		}
		break;
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (Game) {
	case START:
		break;
	case PLAY:
		player_->DrawUI();
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
