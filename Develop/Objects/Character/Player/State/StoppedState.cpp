#include "StoppedState.h"

#include "DxLib.h"
#include "../../../../Utility/InputManager.h"
#include "../Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[���</param>
StoppedState::StoppedState(class Player* p)
	: PlayerStateBase(p)
	, input(nullptr)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StoppedState::~StoppedState()
{

}

/// <summary>
/// ����������
/// </summary>
void StoppedState::Initialize()
{
	//Box�̃T�C�Y��ݒ肷��
	player->box_size = Vector2D(32.0f);

	//���͏����擾
	input = InputManager::Get();
}

/// <summary>
/// �I������
/// </summary>
void StoppedState::Finalize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void StoppedState::Update()
{
	//�ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		//�ړ���ԂɑJ��
		player->SetNextState(ePlayerState::eRun);
	}

	//�W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::eJump);
	}

	//���Ⴊ�ݏ�ԂɑJ��
	if (input->GetKey(KEY_INPUT_S))
	{
		//�ړ���ԂɑJ��
		player->SetNextState(ePlayerState::eSquat);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void StoppedState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	/*DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(255, 0, 0), TRUE);*/
}

/// <summary>
/// ���݂̃X�e�[�g�����擾����
/// </summary>
/// <returns>���݂̃X�e�[�g���</returns>
ePlayerState StoppedState::GetState() const
{
	return ePlayerState::eIdle;
}