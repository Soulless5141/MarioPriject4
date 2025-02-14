#include "RunningState.h"

#include "DxLib.h"
#include "../Player.h"

#define MAX_SPEED (4.0f)

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
	accel_force = 0.0f;
	//���͏����擾
	input = InputManager::Get();
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
	accel_force = FRICTION / 444.0f;
	if (input->GetKey(KEY_INPUT_A))
	{
		player->SetReverse(true);
		if (input->GetKey(KEY_INPUT_LSHIFT))
		{
			if (player->velocity.x > (-MAX_SPEED * 1.75f))
			{
				player->velocity.x -= accel_force;
			}
		}
		else
		{
			if (player->velocity.x > -MAX_SPEED)
			{
				player->velocity.x -= accel_force;
			}
			else
			{
				player->velocity.x += accel_force;
			}
		}
		player->f_velocity = 0.0f;
	}
	else if (input->GetKey(KEY_INPUT_D))
	{
		player->SetReverse(false);
		if (input->GetKey(KEY_INPUT_LSHIFT))
		{
			if (player->velocity.x < (MAX_SPEED * 1.75f))
			{
				player->velocity.x += accel_force;
			}
		}
		else
		{
			if (player->velocity.x < MAX_SPEED)
			{
				player->velocity.x += accel_force;
			}
			else
			{
				player->velocity.x -= accel_force;
			}
		}

		player->f_velocity = 0.0f;
	}
	else
	{
		//��~��ԂɑJ��
		player->SetNextState(ePlayerState::eIdle);
		accel_force = 0.0f;
	}
	if (input->GetKey(KEY_INPUT_SPACE))
	{
		player->velocity.y -= (D_GRAVITY / 444.0f) / 1.2;
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