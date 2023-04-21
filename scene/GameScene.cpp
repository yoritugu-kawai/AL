#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

#include"ImGuiManager.h"
#include"PrimitiveDrawer.h"
#include"AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	//デストラクタ
	
	delete sprite_;

	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// スプライト
	textureHandle_ = TextureManager::Load("kamata.ico");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// 3d
	textureHandle2_ = TextureManager::Load("kamata.ico");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	// サウンド
	soundDateHandle_ = audio_->LoadWave("mokugyo.wav");
	audio_->PlayWave(soundDateHandle_);
	voiceHandle_ = audio_->PlayWave(soundDateHandle_, true);
	//ライン
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
	// カメラ
	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
  }

void GameScene::Update() { 
	// スプライト
	Vector2 position = sprite_->GetPosition();

	position.x += 2.0f;
	position.y += 1.0f;

	sprite_->SetPosition(position);
	// サウンド
	if (input_->TriggerKey(DIK_SPACE)) {
	
	audio_->StopWave(voiceHandle_);
	}
	// デバックウインドウ
	ImGui::Begin("Debug1");
	ImGui::Text("kamata tarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("InoutFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::ShowDemoWindow();
	ImGui::End();
	// カメラ
	debugCamera_->Update();

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

	sprite_->Draw();

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
	
	model_->Draw(worldTransform_, viewProjection_, textureHandle2_);
	//
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle2_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 10, 0}, {0, 100, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
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
