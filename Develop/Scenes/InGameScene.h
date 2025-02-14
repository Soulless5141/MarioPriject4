#pragma once
#include"SceneBase.h"
#include"../Objects/Character/Player/Player.h"
#include "../Utility/Camera.h"

#define BLOCK_MAX_X (211)
#define BLOCK_MAX_Y (15)

class InGameScene : public SceneBase
{
private:
	class Player* player;		// プレイヤー情報
	Camera* camera;
	int back_ground_stage;		// 背景画像
	int ground_stage;		// 背景画像
	int back_bgm;		// 背景画像
	bool pause_flag;			// 一時停止フラグ

	int ui_time;                // 画面右上の制限時間描画（TIME）400スタートで減っていく
	int ui_world;               // 画面右上の制限時間の左側にある現在マップの描画（WORLD 1-1）
	//int ui_coin_1_score;          // 画面左上のマリオスコアの右側にある獲得したコイン枚数の描画（ × 00）
	int ui_mario_score;         // 画面左上のマリオスコアの描画（MARIO 000000）
	std::vector<int>ui_coin_1_score;          // 画面左上のマリオスコアの右側にある獲得したコイン枚数の描画（ × 00）

	std::vector<std::vector<int>>haikei_block;
	std::vector<std::vector<int>>block;
	std::vector<std::vector<GameObject*>>object;
	std::vector<int>ui_num;

	//// 背景画像の読み込み
	//ResourceManager* rm = ResourceManager::GetInstance();
	//GameObjectManager* gm = GameObjectManager::GetInstance();

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;	

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// 当たり判定確認処理
	/// </summary>
	/// <param name="target">1つ目のゲームオブジェクト</param>
	/// <param name="partner">2つ目のゲームオブジェクト</param>
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	/// <summary>
	/// ステージマップ（壁）読み込み処理
	/// </summary>
	void LoadStageMapCSV();
	/// <summary>
	/// ステージマップ読み込み処理
	/// </summary>
	void LoadBackStageMapCSV();
	/// <summary>
	/// ステージ生成
	/// </summary>
	void CreateStage();
	/// <summary>
	/// オブジェクト削除
	/// </summary>
	void DeleteStage();
};

