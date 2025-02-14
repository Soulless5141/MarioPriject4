#include "SquatState.h"

#include "DxLib.h"
#include "../Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[���</param>
SquatState::SquatState(class Player* p)
	: PlayerStateBase(p)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SquatState::~SquatState()
{

}

/// <summary>
/// ����������
/// </summary>
void SquatState::Initialize()
{
	ResourceManager* rm = ResourceManager::Get();
	//���͏����擾
	input = InputManager::Get();
	if (player->GetPlayerMode() == ePlayerMode::DEKAMARIO)
	{
		player->box_size.y = 32.0f;
	}

}

/// <summary>
/// �I������
/// </summary>
void SquatState::Finalize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void SquatState::Update()
{

	//�n�ʂɐG�ꂽ��
	if (player->velocity.y >= 0)
	{

		if (input->GetKey(KEY_INPUT_S))
		{
			player->SetNextState(ePlayerState::eSquat);
		}
		else
		{
			//��~��ԂɑJ��
			
			player->SetNextState(ePlayerState::eIdle);
		}
	}
	if (input->GetKey(KEY_INPUT_A) || input->GetKey(KEY_INPUT_D))
	{
		//�ړ���ԂɑJ��
		player->SetNextState(ePlayerState::eRun);
	}

	if (player->velocity.x >= 0.5f)
	{
		player->velocity.x -= player->f_velocity;
	}
	else if (player->velocity.x <= -0.5f)
	{
		player->velocity.x += player->f_velocity;
	}
	else
	{
		player->velocity.x = 0.0f;
		player->f_velocity = 0.0f;
	}

}

/// <summary>
/// �`�揈��
/// </summary>
void SquatState::Draw() const
{
	//���W���𐮐��l�ɕϊ�
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	//�`��
	/*DrawBox(x, y, x + (int)(player->box_size.x), y + (int)(player->box_size.y),
		GetColor(0, 0, 255), FALSE);*/
}

/// <summary>
/// ���݂̃X�e�[�g�����擾����
/// </summary>
/// <returns>���݂̃X�e�[�g���</returns>
ePlayerState SquatState::GetState() const
{
	return ePlayerState::eSquat;
}

