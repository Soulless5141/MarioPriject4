#include "Player.h"

#include <cmath>

#include "../../../Utility/InputManager.h"
#include "State/Factory/PlayerStateFactory.h"
#include "../../../Utility/Camera.h"
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
	move_time(0),
	damage_time(0.0f),
	is_fly(false),
	player_mode(ePlayerMode::MARIO),
	sound()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::Get();
	dekamarimation_animation = rm->GetImages("Resource/Images/Mario/dekamarimation.png", 3, 3, 1, 32, 64);
	dekamario_animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);
	faiyamario_animation = rm->GetImages("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 32);
	mario_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	//starmario_animation = rm->GetImages("Resource/Images/Mario/starmario.png", 11, 11, 1, 32, 32);
	//starsmallmario_animation = rm->GetImages("Resource/Images/Mario/starsmallmario.png", 11, 11, 1, 32, 32);
	player_mode = ePlayerMode::MARIO;
	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.box_size = 32.0f;
	collision.pivot = location;
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
	is_fly = FALSE;
	reverse = FALSE;
	// �����̐ݒ�
	
}

void Player::Update(float delta_second)
{
	if (power_up_time <= 0.0f && power_down_time <= 0.0f)
	{
		//�ړ�����
		Movement(delta_second);

		//��ԕʂ̕`�揈�����s��
		AnimationControl(delta_second);

		damage_time -= delta_second;
		if (damage_time <= 0.0f)
		{
			damage_time = 0.0f;
		}

		power_up_time = 0.0f;
	}
	else
	{
		if (power_up_time > 0.0f)
		{
			PowerUpAnim(delta_second);
		}
		else if (power_down_time > 0.0f)
		{
			//��ԕʂ̕`�揈�����s��
			AnimationControl(delta_second);
		}
	}

}

void Player::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
	DrawFormatString(100, 100, 0x000000, "%f", damage_time);
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
	Collision oc = hit_object->GetCollision();
	Vector2D diff;
	Vector2D dis;

	// ���������A�I�u�W�F�N�g���ǂ�������
	if (oc.object_type == eObjectType::eBlock)
	{
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//�v���C���[�̉E���ƃI�u�W�F�N�g�̍���̔���
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);
				
				//�����߂�
				if (diff.x <= diff.y && diff.x != 0.0f)
				{
					location.x -= diff.x;
					velocity.x = 0.0f;
				}
				else if(diff.x != 0.0f)
				{
					location.y -= diff.y;
					is_fly = false;
					velocity.y = 0;
				}
			}
			else
			{
				//�v���C���[�̉E��ƃI�u�W�F�N�g�̍����̔���
				diff = Vector2D((this->location.x + collision.box_size.x / 2), (this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - oc.box_size.x / 2), (hit_object->GetLocation().y + oc.box_size.y / 2));

				//�����߂�
				if (diff.x > diff.y && dis.y <= box_size.y / 2)
				{
					location.x -= diff.x;
					velocity.x = 0.0f;
				}
				else if(diff.x != 0.0f)
				{
					location.y -=  diff.y;
					velocity = 0.0f;
				}

			}
		}
		else
		{
			if (dis.y >= 0)
			{
				//�v���C���[�̍���ƃI�u�W�F�N�g�̉E���̔���
				diff = (this->location - collision.box_size / 2) - (hit_object->GetLocation() + oc.box_size / 2);

				//�����߂�
				if (-diff.x < -diff.y || dis.y == 0)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					velocity = 0.0f;
				}
			}
			else
			{
				//�v���C���[�̍����ƃI�u�W�F�N�g�̉E��̔���
				diff = Vector2D((this->location.x - collision.box_size.x / 2), (this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + oc.box_size.x / 2), (hit_object->GetLocation().y - oc.box_size.y / 2));

				//�����߂�
				if (-diff.x < diff.y)
				{
					location.x -= diff.x;
				}
				else
				{
					location.y -= diff.y;
					is_fly = false;
					velocity.y = 0;
				}
			}
		}
	}

	// ���������A�I�u�W�F�N�g���G��������
	if (oc.object_type == eObjectType::eEnemy)
	{
		dis = this->location - hit_object->GetLocation();

		if (dis.x <= 0)
		{
			if (dis.y <= 0)
			{
				//�v���C���[�̉E���ƃI�u�W�F�N�g�̍���̔���
				diff = (this->location + collision.box_size / 2) - (hit_object->GetLocation() - oc.box_size / 2);

				//�����߂�
				if (diff.x <= diff.y)
				{
					if (damage_time <= 0.0f)
					{
						if (player_mode == ePlayerMode::DEKAMARIO)
						{
							collision.box_size.y = 32.0f;
						}
						power_down_time = 0.5f;
						player_state = ePlayerState::eDamage;
						damage_time = 1.0f;
					}					
				}
				else
				{
					g_velocity = 0.0f;
					velocity.y = -3.0f;
				}
			}
			else
			{
				if (damage_time <= 0.0f)
				{
					if (player_mode == ePlayerMode::DEKAMARIO)
					{
						collision.box_size.y = 32.0f;
					}
					power_down_time = 0.5f;
					player_state = ePlayerState::eDamage;
					damage_time = 1.0f;
				}
			}
		}
		else
		{
			if (dis.y >= 0)
			{
				if (damage_time <= 0.0f)
				{
					if (player_mode == ePlayerMode::DEKAMARIO)
					{
						collision.box_size.y = 32.0f;
					}
					power_down_time = 0.5f;
					player_state = ePlayerState::eDamage;
					damage_time = 1.0f;
				}
			}
			else
			{
				//�v���C���[�̍����ƃI�u�W�F�N�g�̉E��̔���
				diff = Vector2D((this->location.x - collision.box_size.x / 2), (this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + oc.box_size.x / 2), (hit_object->GetLocation().y - oc.box_size.y / 2));

				//�����߂�
				if (-diff.x < diff.y)
				{
					if (damage_time <= 0.0f)
					{
						if (player_mode == ePlayerMode::DEKAMARIO)
						{
							collision.box_size.y = 32.0f;
						}
						power_down_time = 0.5f;
						player_state = ePlayerState::eDamage;
						damage_time = 1.0f;
					}
				}
				else
				{
					g_velocity = 0.0f;
					velocity.y = -3.0f;
				}
			}
		}
	}

	if (oc.object_type == eObjectType::eItem)
	{
		if (player_mode == ePlayerMode::MARIO)
		{
			location.y -= 16.0f;
			collision.box_size.y = 64.0f;
			player_mode = ePlayerMode::DEKAMARIO;

			power_up_time = 0.5f;
		}
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
	Camera* camera = Camera::Get();
	// state�̕ύX����
	state = PlayerStateFactory::Get((*this), player_state);

	//�d�͑��x�̌v�Z
	g_velocity = D_GRAVITY / 444.0f;
	f_velocity = FRICTION / 444.0f;

	/*move_time += delta_second;
	if (move_time >= (1.0f / 30.0f))
	{*/
	velocity.y += g_velocity;

		

	//��ԕʂ̍X�V�������s��
	state->Update();

	//�ړ��̎��s
	location += velocity * D_PLAYER_SPEED * delta_second;

	//384.0f�n�_��n�ʂƉ���
	if (is_fly != true)
	{
		g_velocity = 0.0f;
	}
	if (location.x < camera->GetCameraLocation().x - (D_WIN_MAX_X / 2.1))
	{
		location.x = camera->GetCameraLocation().x - (D_WIN_MAX_X / 2.1);
		velocity.x = 0;
	}
	//if (location.y >= 384.0f)
	//{
	//	location.y = 384.0f;
	//	g_velocity = 0.0f;
	//	velocity.y = 0.0f;
	//}
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
		case DEKAMARIO:
			image = dekamario_animation[0];
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			image = mario_animation[0];
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}

		break;
	case ePlayerState::eRun:
		switch (player_mode)
		{
		case DEKAMARIO:
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
				image = dekamario_animation[animation_num[animation_count] + 1];

			}
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
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
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
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
		break;
	case ePlayerState::eSquat:
		switch (player_mode)
		{
		case DEKAMARIO:
			image = dekamario_animation[1];
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
		break;
	case ePlayerState::eDamage:
		switch (player_mode)
		{
		case DEKAMARIO:
			PowerDownAnim(delta_second);
			if (power_down_time <= 0.0f)
			{
				player_mode = ePlayerMode::MARIO;
			}
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			power_down_time -= delta_second;
			image = mario_animation[6];
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}
	
		break;
	case ePlayerState::eGoal:
		break;
	default:
		break;
	}

	if (is_fly == true)
	{
		switch (player_mode)
		{
		case DEKAMARIO:
			image = dekamario_animation[6];
			break;
		case FAIYAMARIO:
			break;
		case MARIO:
			image = mario_animation[5];
			break;
		case STARMARIO:
			break;
		case STARSMALLMARIO:
			break;
		default:
			break;
		}

	}

}

void Player::PowerUpAnim(float delta_second)
{
	power_up_time -= delta_second;
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// �摜�̐ݒ�
		image = dekamarimation_animation[animation_count];
	}
}

void Player::PowerDownAnim(float delta_second)
{
	power_down_time -= delta_second;
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count--;
		if (animation_count <= 0)
		{
			animation_count = 2;
		}
		// �摜�̐ݒ�
		image = dekamarimation_animation[animation_count];
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

void Player::SetReverse(bool TF)
{
	reverse = TF;
}

float Player::GetPowerUpTime()
{
	return this->power_up_time;
}

float Player::GetPowerDownTime()
{
	return this->power_down_time;
}