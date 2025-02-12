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
	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::Get();
	
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];

	ui_time = rm->GetImages("Resource/Images/UI/time.png")[0];

	ui_world = rm->GetImages("Resource/Images/UI/world.png")[0];

	ui_coin_1_score = rm->GetImages("Resource/Images/UI/uicoin_1.png")[0];

	ui_mario_score = rm->GetImages("Resource/Images/UI/name_mario.png")[0];

	ui_top_score = rm->GetImages("Resource/Images/UI/top.png")[0];
}

eSceneType TitleScene::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::Get();

	// �C���Q�[���V�[���ɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void TitleScene::Draw() 
{
	// �^�C�g����ʐ���
	DrawExtendGraph(0, 0, 672, 480, back_ground_image, FALSE);

	DrawExtendGraph(510, 20, 580, 42, ui_time, TRUE);

	DrawExtendGraph(380, 20, 470, 42, ui_world, TRUE);

	DrawExtendGraph(220, 43, 310, 63, ui_coin_1_score, TRUE);

	DrawExtendGraph(90, 20, 180, 42, ui_mario_score, TRUE);

	DrawExtendGraph(260, 365, 340, 385, ui_top_score, TRUE);

	DrawFormatString(190, 300, GetColor(255, 255, 255), "SPACEKEY");

	DrawFormatString(290, 300, GetColor(255, 255, 255), "1  PLAYER  GAME");

	DrawFormatString(340, 265, GetColor(255, 200, 200), "1985 NINTENDO");

}

void TitleScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
