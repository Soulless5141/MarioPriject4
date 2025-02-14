#include "DamageState.h"

#include "DxLib.h"
#include "../Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="p">�v���C���[���</param>
DamageState::DamageState(class Player* p)
	: PlayerStateBase(p)
	, input(nullptr)
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DamageState::~DamageState()
{

}

/// <summary>
/// ����������
/// </summary>
void DamageState::Initialize()
{
	//Box�̃T�C�Y��ݒ肷��
	player->box_size = Vector2D(32.0f);

	//���͏����擾
	input = InputManager::Get();
}

/// <summary>
/// �I������
/// </summary>
void DamageState::Finalize()
{

}

/// <summary>
/// �X�V����
/// </summary>
void DamageState::Update()
{
	accel_force = FRICTION / 444.0f;
	if (input->GetKey(KEY_INPUT_A))
	{
		player->SetReverse(true);
		if (input->GetKey(KEY_INPUT_LSHIFT))
		{
			if (player->velocity.x > -8.0f)
			{
				player->velocity.x -= accel_force;
			}
		}
		else
		{
			if (player->velocity.x > -4.0f)
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
			if (player->velocity.x < 8.0f)
			{
				player->velocity.x += accel_force;
			}
		}
		else
		{
			if (player->velocity.x < 4.0f)
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
	if (player->damage_time <= 0.5f)
	{
		player->SetNextState(ePlayerState::eIdle);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void DamageState::Draw() const
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
ePlayerState DamageState::GetState() const
{
	return ePlayerState::eDamage;
}