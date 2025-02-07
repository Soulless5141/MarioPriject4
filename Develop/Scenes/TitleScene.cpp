#include "TitleScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::Get();
	
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];

	ui_time = rm->GetImages("Resource/Images/UI/time.png")[0];
}

eSceneType TitleScene::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::Get();

	// インゲームシーンに遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void TitleScene::Draw() 
{
	// タイトル画面生成
	DrawExtendGraph(0, 0, 672, 480, back_ground_image, FALSE);

	DrawExtendGraph(520, 20, 0, 0, ui_time, FALSE);

	DrawFormatString(180, 300, GetColor(255, 255, 255), "SPACEKEY");

	DrawFormatString(270, 300, GetColor(255, 255, 255), "1  PLAYER  GAME");

	DrawFormatString(290, 360, GetColor(255, 255, 255), "TOP- 000000");

	DrawFormatString(340, 265, GetColor(255, 200, 200), "1985 NINTENDO");

	DrawFormatString(520, 20, GetColor(255, 255, 255), "TIME");

	DrawFormatString(420, 20, GetColor(255, 255, 255), "WORLD");

	DrawFormatString(430, 40, GetColor(255, 255, 255), "1-1");

	DrawFormatString(260, 40, GetColor(255, 255, 255), "× 00");

	DrawFormatString(110, 20, GetColor(255, 255, 255), "MARIO");

	DrawFormatString(110, 40, GetColor(255, 255, 255), "000000");


}

void TitleScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
