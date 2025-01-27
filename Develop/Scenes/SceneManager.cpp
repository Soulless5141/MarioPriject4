#include "SceneManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "InGameScene.h"
#include "ResultScene.h"
#include "../Utility/Application.h"

SceneManager::SceneManager() :
	current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{
	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	ChangeScene(eSceneType::title);
}

bool SceneManager::Update(float delta_second)
{
	// �V�[���̍X�V
	eSceneType next_scene_type = current_scene->Update(GetDeltaSecond());

	// �`�揈��
	Graph();

	// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// �V�[���؂�ւ�����
		ChangeScene(next_scene_type);
	}

	return 0;
}

void SceneManager::Finalize()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

 /*<summary>
 �V�[���؂�ւ�����
 </summary>
 <param name="next_type">���̃V�[���^�C�v</param>*/
void SceneManager::ChangeScene(eSceneType next_type)
{
	// ���̃V�[���𐶐�����
	SceneBase* next_scene = CreateScene(next_type);

	// �G���[�`�F�b�N
	if (next_scene == nullptr)
	{
		throw ("�V�[���������ł��܂���ł���\n");
	}

	// �V�[����񂪊i�[����Ă�����A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// ���̃V�[���̏�����
	next_scene->Initialize();

	// ���݃V�[���̏㏑��
	current_scene = next_scene;
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="next_type">���̃V�[���^�C�v</param>
/// <returns>���������V�[�����̃|�C���^</returns>
SceneBase* SceneManager::CreateScene(eSceneType next_type)
{
	// �V�[���^�C�v�ɂ���āA��������V�[����؂�ւ���
	switch (next_type)
	{
	case eSceneType::title:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::in_game:
	case eSceneType::re_start:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::result:
		return dynamic_cast<SceneBase*>(new ResultScene());
	default:
		return nullptr;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Graph() const
{
	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`�揈��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}