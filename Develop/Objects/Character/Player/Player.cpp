#include "Player.h"

#include <cmath>

#include "../../../Utility/InputManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "DxLib.h"

#define D_PLAYER_SPEED	(50.0f)
#define D_GRAVITY (9.807f)     //�d�͉����x(m/ss)

Player::Player() :
	dekamarimation_animation(),
	dekamario_animation(),
	faiyamario_animation(),
	mario_animation(),
	starmario_animation(),
	starsmallmario_animation(),
	velocity(0.0f),
	player_state(ePlayerState::eIdle),
	animation_time(0.0f),
	animation_count(0),
	power_up_time(0),
	enemy(NULL),
	move_time(0)
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::Get();
	dekamarimation_animation = rm->GetImages("Resource/Images/Mario/dekamarimation.png", 3, 3, 1, 32, 32);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 32);
	faiyamario_animation = rm->GetImages("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 32);
	mario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	//starmario_animation = rm->GetImages("Resource/Images/Mario/starmario.png", 11, 11, 1, 32, 32);
	//starsmallmario_animation = rm->GetImages("Resource/Images/Mario/starsmallmario.png", 11, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	// �����̃A�j���[�V����
	image = mario_animation[0];

	// ���C���[�̐ݒ�
	z_layer = 5;

	//�����X�e�[�^�X�ݒ�
	player_state = ePlayerState::eIdle;
	g_velocity = 0;
	velocity = Vector2D(0.0);

	// �����̐ݒ�
	is_mobility = eMobilityType::Movable;
}

void Player::Update(float delta_second)
{
	//�ړ�����
	Movement(delta_second);

	//��ԕʂ̕`�揈�����s��
	AnimationControl(delta_second);
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

// �I������
void Player::Finalize()
{
	PlayerStateFactory::Finalize();

	// ���I�z��̉��
	dekamarimation_animation.clear();
	mario_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Player::OnHitCollision(GameObject* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
		
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
ePlayerMode Player::GetPlayerMode() const
{
	return player_mode;
}

ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

void Player::SetDefoltX()
{
	animation_count = 0;
}


/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Movement(float delta_second)
{
	// state�̕ύX����
	state = PlayerStateFactory::Get((*this), player_state);

	//�d�͑��x�̌v�Z
	g_velocity = D_GRAVITY / 444.0f;

	/*move_time += delta_second;
	if (move_time >= (1.0f / 30.0f))
	{*/
	velocity.y += g_velocity;

	//��ԕʂ̍X�V�������s��
	state->Update();

	//�ړ��̎��s
	location += velocity * D_PLAYER_SPEED * delta_second;

	//384.0f�n�_��n�ʂƉ���
	if (384.0f <= location.y)
	{
		location.y = 384.0f;
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}
	if (0.0 >= location.x)
	{
		location.x = 0.0f;
	}
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{
	switch (player_state)
	{
	case ePlayerState::eIdle:
		switch (player_mode)
		{
		case DEKAMARIMATION:
			break;
		case DEKAMARIO:
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}
		image = mario_animation[0];
		break;
	case ePlayerState::eRun:

		// �ړ����̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 4)
			{
				animation_count = 0;
			}
			// �摜�̐ݒ�
			image = mario_animation[animation_num[animation_count]];

		}
		
		// �摜���]����
		if (velocity.x < 0 && velocity.y == 0)
		{
			reverse = true;
		}
		else if (velocity.x > 0 && velocity.y == 0)
		{
			reverse = false;
		}

		break;
	case ePlayerState::eJump:
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		break;
	case ePlayerState::sSquat:
		break;
	case ePlayerState::eDamage:
		break;
	case ePlayerState::eGoal:
		break;
	default:
		break;
	}

	if (velocity.y != 0)
	{
		image = mario_animation[5];
	}
}


/// <summary>
/// ����state��ݒ�
/// </summary>
/// <param name="next_state">����State</param>
void Player::SetNextState(ePlayerState next_state)
{
	this->player_state = next_state;
}

/// <summary>
/// ���W�̎擾
/// </summary>
Vector2D& Player::GetLocation()
{
	return this->location;
}

