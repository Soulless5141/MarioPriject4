#include "RunningState.h"

#include "DxLib.h"
#include "../../../../Utility/InputManager.h"
#include "../Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[���</param>
RunningState::RunningState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
RunningState::~RunningState()
{

}

/// <summary>
/// ����������
/// </summary>
void RunningState::Initialize()
{
	if (this->player->velocity.x == 0)
	{
		this->player->SetDefoltX();
	}
}

/// <summary>
/// �I������
/// </summary>
void RunningState::Finalize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void RunningState::Update()
{
	//���E���͂�����Ȃ�
	InputManager* input = InputManager::Get();

	if (input->GetKey(KEY_INPUT_A))
	{
		player->velocity.x = -4.0f; //�ړ���
	}
	else if (input->GetKey(KEY_INPUT_D))
	{
		player->velocity.x = 4.0f; //�ړ���
	}
	else
	{
		player->velocity.x = 0.0f; //�ړ��͏���
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::eIdle);
	}

	if (input->GetKeyDown(KEY_INPUT_SPACE) && player->velocity.x != 0)
	{
		//�ړ���ԂɑJ��
		player->SetNextState(ePlayerState::eJump);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void RunningState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(255, 0, 0), TRUE);
}

/// <summary>
/// ���݂̃X�e�[�g�����擾����
/// </summary>
/// <returns>���݂̃X�e�[�g���</returns>
ePlayerState RunningState::GetState() const
{
	return ePlayerState::eRun;
}