#pragma once

#include "SceneBase.h"

// タイトルシーン
class TitleScene : public SceneBase
{
private:

	int back_ground_image;      // タイトルの背景画像
	int ui_time;                // 画面右上の制限時間描画（TIME）
	int ui_world;               // 画面右上の制限時間の左側にある現在マップの描画（WORLD 1-1）
	//int ui_coin_1_score;          // 画面左上のマリオスコアの右側にある獲得したコイン枚数の描画（ × 00）
	int ui_mario_score;         // 画面左上のマリオスコアの描画（MARIO 000000）
	int ui_1_player;            // 画面中央少し下のプレイヤー人数選択の描画（１ PLAYER GAME）
	int ui_top_score;           // 画面中央下、プレイヤー人数選択の下側にあるハイスコアの描画（TOP- 000000）
	std::vector<int>ui_coin_1_score;          // 画面左上のマリオスコアの右側にある獲得したコイン枚数の描画（ × 00）

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;
};

